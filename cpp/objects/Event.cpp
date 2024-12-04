#include "Event.h"

Event::Event(QObject *parent)
    : QObject{parent}
    , m_detachedTeam(nullptr)
    , m_phase(Phase::First)
    , m_stage(Stage::None)
    , m_round(1)
    , m_roundStage(firstRoundStage)
{
}

Event::~Event()
{
    this->clearTeams();
}

void Event::clearTeams()
{
    for(Team *team : m_teams[Phase::First])
        delete team;
    m_teams[Phase::First].clear();

    for(Team *team : m_teams[Phase::Second])
        delete team;
    m_teams[Phase::Second].clear();

    emit this->teamsChanged();
}

void Event::clearMatches()
{
    for(Match *match : m_matches[Phase::First])
        delete match;
    m_matches[Phase::First].clear();

    for(Match *match : m_matches[Phase::Second])
        delete match;
    m_matches[Phase::Second].clear();

    emit this->matchesChanged();
}

void Event::clearEvent()
{
    this->clearTeams();
    this->clearMatches();
    this->setPhase(Event::Phase::First);
    this->setName("");

}

void Event::validateConfigureData()
{
    /// this should be called only after starting the event before continue stage

    if(m_phase == Phase::First)
    {
        this->validateConfigureFirstPhaseData();
    }
    else
    {
        this->validateConfigureSecondPhaseData();
    }
}

void Event::createExampleConfigureData()
{
    // this->clearEvent();
    this->blockSignals(true);

    QJsonArray jTeams = Personalization::getInstance()->getExampleData()["teams"].toArray();
    for(int i=0; i<jTeams.size(); i++)
    {
        QJsonObject jTeam = jTeams[i].toObject();

        this->createDetachedTeam();
        Team *team = m_detachedTeam;
        team->blockSignals(true);

        team->setTeamName( jTeam["team name"].toString() );

        QJsonArray jPlayers = jTeam["players"].toArray();
        for(int j=0; j<jPlayers.size(); j++)
        {
            QJsonObject jPlayer = jPlayers[j].toObject();

            team->createDetachedPlayer();
            Player *player = team->getDetachedPlayer();

            player->setFname( jPlayer["fname"].toString() );
            player->setLname( jPlayer["lname"].toString() );
            player->setLicense( jPlayer["license"].toString() );
            player->setAgeGroup( jPlayer["age group"].toInt() );
            player->setGender( jPlayer["gender"].toInt() );
            player->setIsTeamLeader( jPlayer["isTeamLeader"].toBool() );

            team->addPlayerUsingDetachedPlayer();
        }

        team->blockSignals(false);
        emit team->playersChanged();

        this->addTeamUsingDetachedTeam();
    }

    this->blockSignals(false);
    emit this->teamsChanged();
}

void Event::createDetachedTeam()
{
    // I("Creating detached Team")
    if(m_detachedTeam != nullptr)
    {
        W("Creating new detached Team, while old wasn't deleted")
    }

    m_detachedTeam = new Team(this);
    m_detachedTeam->setTeamID( this->generateUniqueTeamID() );
    emit this->detachedTeamChanged();
}

void Event::deleteDetachedTeam()
{
    // I("Deleting detached Team")
    if(m_detachedTeam == nullptr)
    {
        E("trying to delete aleady deleted detached Team")
        return;
    }

    delete m_detachedTeam;
    m_detachedTeam = nullptr;
    // emit this->detachedTeamChanged();
}

void Event::addTeamUsingDetachedTeam()
{
    // I("Adding detached Team to Event")
    Team *team = m_detachedTeam;
    m_detachedTeam = nullptr;

    if(!this->isTeamIDUniqueInTeamssList( team->getTeamID() ))
        W("In the meantime creating detached Team, teamID{" +
          QString::number(team->getTeamID()) +
          "} was changed to not unique (in relation to teams list)");

    m_teams[m_phase].append(team);
    emit this->teamsChanged(); // this slows down program, but can be muted
}

void Event::deleteTeam(const Team * const team)
{
    /// should be used only for phase 1
    int index = -1;
    for(int i=0; i<m_teams[Phase::First].size(); i++)
    {
        if(team == m_teams[Phase::First][i])
        {
            index = i;
            break;
        }
    }

    if(index == -1)
    {
        W(QString::asprintf("Team to delete %p was not found!", team))
        return;
    }

    delete m_teams[Phase::First][index];
    m_teams[Phase::First].remove(index);

    emit this->teamsChanged();
}

void Event::addJudge()
{
    m_judges.append("");
    emit this->judgesChanged();
}

void Event::deleteJudge(int index)
{
    if(index >= m_judges.size())
    {
        W("trying to delete not existing judge")
        return;
    }

    m_judges.remove(index);
    emit this->judgesChanged();
}

void Event::setJudge(int index, QString judge)
{
    if(index >= m_judges.size())
    {
        W("trying to acces not existing judge")
        return;
    }

    m_judges[index] = judge;
    emit this->judgesChanged();
}

void Event::goToNextStage()
{
    if(m_stage >= Stage::Finish)
    {
        W("trying to exceed the highest stage!");
        return;
    }
    m_stage = static_cast<Stage>( m_stage+1 );
    emit this->stageChanged();
}

void Event::goToPrevStage()
{
    if(m_stage <= Stage::Configure)
    {
        W("trying to exceed the lowest stage!");
        return;
    }
    m_stage = static_cast<Stage>( m_stage-1 );
    emit this->stageChanged();
}

void Event::goToConfigureStage()
{
    if(m_stage == Stage::Configure)
    {
        W("stage is already at Configure");
        return;
    }
    m_stage = Stage::Configure;
    emit this->stageChanged();
}

void Event::goToNextRoundStage()
{
    if(m_round >= Personalization::getInstance()->getRoundsCount() && m_roundStage == Event::lastRoundStage)
    {
        W("trying to go forward to much")
        return;
    }

    if(m_roundStage == Event::lastRoundStage)
    {
        m_roundStage = Event::firstRoundStage;
        m_round++;
        emit this->roundStageChanged();
        emit this->roundChanged();
    }
    else
    {
        m_roundStage = static_cast<RoundStage>(m_roundStage +1);
        emit this->roundStageChanged();
    }

}

void Event::goToPrevRoundStage()
{
    if(m_round <= 1 && m_roundStage == Event::firstRoundStage)
    {
        W("trying to go back to much")
        return;
    }

    if(m_roundStage == Event::firstRoundStage)
    {
        m_roundStage = Event::lastRoundStage;
        m_round--;
        emit this->roundStageChanged();
        emit this->roundChanged();
    }
    else
    {
        m_roundStage = static_cast<RoundStage>(m_roundStage -1);
        emit this->roundStageChanged();
    }
}

void Event::goToFirstRoundStage()
{
    if(m_roundStage == Event::firstRoundStage)
    {
        W("roundStage is already first")
    }
    else
    {
        m_roundStage = Event::firstRoundStage;
        emit this->roundStageChanged();
    }

    if(m_round == 1)
    {
        W("round is already first round")
    }
    else
    {
        m_round = 1;
        emit this->roundChanged();
    }
}

void Event::createMatchIfNotExist()
{
    /// for n round should be n matches created
    if(m_round > m_matches[m_phase].size())
    {
        /// create match
        this->createNewMatch();
        emit this->matchWasCreated();
    }
    else
    {
        /// match already created and can be used
        // D("Match exist")
        emit this->matchAlreadyExist();
    }
}

Match *Event::createNewMatch(bool assignMatchCombinations)
{
    Match *match = new Match(this);

    if(assignMatchCombinations)
    {
        QString matchNumber = "r" + QString::number(m_matches[m_phase].size()+1);
        QJsonArray matchCombinations = Personalization::getInstance()->getRoundsMatches()[matchNumber].toArray();
        for(const auto &_matchCombination : matchCombinations)
        {
            QJsonObject matchCombination = _matchCombination.toObject();
            match->addMatchCombination(matchCombination["t1"].toInt(), matchCombination["t2"].toInt());
        }
    }

    for(int i=0; i<m_teams[m_phase].size(); i++)
    {
        MatchTeam *matchTeam = new MatchTeam(match);

        int playersCount = m_teams[m_phase][i]->getPlayers().size();
        MatchTriplets *triplets = new MatchTriplets(playersCount, matchTeam);
        MatchDublets *dublets = new MatchDublets(playersCount, matchTeam);
        MatchSingiels *singiels = new MatchSingiels(playersCount, matchTeam);

        matchTeam->setMatchType(triplets);
        matchTeam->setMatchType(dublets);
        matchTeam->setMatchType(singiels);

        match->addMatchTeam(matchTeam);
    }
    // D("Match created")

    m_matches[m_phase].append(match);
    return match;
}

void Event::verifyCurrentRoundStage()
{
    if(m_roundStage == RoundStage::MatchSummary)
    {
        emit this->currentRoundStageVerified();
        return;
    }

    const MatchTeamList &mtl = m_matches[m_phase][m_round-1]->getMatchTeamList();
    for(int i=0; i<mtl.size(); i++)
    {
        QString errorMessagePrefix(tr("in round %1 and %2 round stage, ").arg(m_round).arg(m_roundStage));
        QString errorMessage;
        QString returnMessage;
        bool ok = true;
        const MatchTeam *const matchTeam = mtl[i];

        switch(m_roundStage)
        {
        case RoundStage::SingielsSelection:
            ok = matchTeam->getMatchType(1)->isSelectionDataValid(&errorMessage);
            if(!ok)
            {
                returnMessage = errorMessagePrefix + tr("in team %1, singiels selection is not valid: %2")
                                                         .arg(m_teams[m_phase][i]->getTeamName(), errorMessage);
                I(returnMessage);
                emit this->currentRoundStageVerificationFailed(returnMessage);
                return;
            }

            break;
        case RoundStage::SingielsMatch:
            ok = matchTeam->getMatchType(1)->isMatchPointsDataValid(&errorMessage);
            if(!ok)
            {
                returnMessage = errorMessagePrefix + tr("in team %1, singiels match points are not valid: %2")
                                                         .arg(m_teams[m_phase][i]->getTeamName(), errorMessage);
                I(returnMessage);
                emit this->currentRoundStageVerificationFailed(returnMessage);
                return;
            }

            break;
        case RoundStage::DubletsSelection:
            ok = matchTeam->getMatchType(2)->isSelectionDataValid(&errorMessage);
            if(!ok)
            {
                returnMessage = errorMessagePrefix + tr("in team %1, dublets selection is not valid: %2")
                                                         .arg(m_teams[m_phase][i]->getTeamName(), errorMessage);
                I(returnMessage);
                emit this->currentRoundStageVerificationFailed(returnMessage);
                return;
            }

            break;
        case RoundStage::DubletsMatch:
            ok = matchTeam->getMatchType(2)->isMatchPointsDataValid(&errorMessage);
            if(!ok)
            {
                returnMessage = errorMessagePrefix + tr("in team %1, dublets match points are not valid: %2")
                                                         .arg(m_teams[m_phase][i]->getTeamName(), errorMessage);
                I(returnMessage);
                emit this->currentRoundStageVerificationFailed(returnMessage);
                return;
            }

            break;
        case RoundStage::TripletsSelection:
            ok = matchTeam->getMatchType(3)->isSelectionDataValid(&errorMessage);
            if(!ok)
            {
                returnMessage = errorMessagePrefix + tr("in team %1, triplets selection is not valid: %2")
                                                         .arg(m_teams[m_phase][i]->getTeamName(), errorMessage);
                I(returnMessage);
                emit this->currentRoundStageVerificationFailed(returnMessage);
                return;
            }

            break;
        case RoundStage::TripletsMatch:
            ok = matchTeam->getMatchType(3)->isMatchPointsDataValid(&errorMessage);
            if(!ok)
            {
                returnMessage = errorMessagePrefix + tr("in team %1, triplets match points are not valid: %2")
                                                         .arg(m_teams[m_phase][i]->getTeamName(), errorMessage);
                I(returnMessage);
                emit this->currentRoundStageVerificationFailed(returnMessage);
                return;
            }

            break;
        case RoundStage::MatchSummary: // shouldn't be reached
            I("there is nothing to verify, in the 'match summary' round stage, all fine");

            break;
        default:
            W("received unknown round stage: " + QString::number(m_roundStage));
        }


    }
    emit this->currentRoundStageVerified();
}

void Event::startSecondPhase()
{
    m_phase = Phase::Second;

    this->copyPlayersFromFirstToSecondPhase();

    emit this->secondPhaseStarted();
}

bool Event::hasNextRoundStage() const
{
    if(m_round != Personalization::getInstance()->getRoundsCount())
        return true;
    else
        return m_roundStage != Event::lastRoundStage;
}

bool Event::hasPrevRoundStage() const
{
    if(m_round != 1)
        return true;
    else
        return m_roundStage != Event::firstRoundStage;
}

void Event::validateConfigureFirstPhaseData()
{
    Personalization *p = Personalization::getInstance();

    /// check if 8 teams was registered
    int teamsCount = m_teams[m_phase].size();
    if(teamsCount != p->getRequiredTeamsCount())
    {
        /// less or more than 8 teams
        QString message = tr("Event requires %1 teams").arg(p->getRequiredTeamsCount());
        I(message);
        emit this->configureDataValidationFailed(message);
        return;
    }

    /// check data for teams:
    for(Team *team : m_teams[m_phase])
    {
        /// check if team has at least 6 players
        int playersCount = team->getPlayers().size();
        if(playersCount < p->getMinimumPlayersInTeam())
        {
            /// team has least than 6 players
            QString message = tr("Team %1 has less than %2 players")
                                  .arg(team->getTeamName())
                                  .arg(p->getMinimumPlayersInTeam());
            I(message);
            emit this->configureDataValidationFailed(message);
            return;
        }

        /// check if team has both genders
        bool foundMale = false;
        bool foundFemale = false;
        for(Player *player : team->getPlayers())
        {
            if(player->getGender() == Player::Gender::Male)
                foundMale = true;

            if(player->getGender() == Player::Gender::Female)
                foundFemale = true;
        }
        if(!foundMale || !foundFemale)
        {
            /// one gender is missing in team
            QString message = tr("Team %1 doesn't contain players of either gender")
                                  .arg(team->getTeamName());
            I(message);
            emit this->configureDataValidationFailed(message);
            return;
        }

        /// check if team has a junior
        if(p->getRequiresJuniors())
        {
            bool foundJunior = false;
            for(Player *player : team->getPlayers())
            {
                if(player->getAgeGroup() == Player::AgeGroup::Junior)
                {
                    foundJunior = true;
                    break;
                }
            }

            if(!foundJunior)
            {
                /// junior player is missing in team
                QString message = tr("Team %1 doesn't contain any junior player")
                                      .arg(team->getTeamName());
                I(message);
                emit this->configureDataValidationFailed(message);
                return;
            }
        }

        /// check if team has one leader
        int foundLeaders = 0;
        for(Player *player : team->getPlayers())
        {
            if(player->getIsTeamLeader())
                ++ foundLeaders;
        }
        if(foundLeaders == 0)
        {
            /// team missing leader
            QString message = tr("In team %1, no leader was selected, each team requires leader")
                                  .arg(team->getTeamName());
            I(message);
            emit this->configureDataValidationFailed(message);
            return;
        }
        else if(foundLeaders > 1)
        {
            /// team contains few leaders
            QString message = tr("Team %1 has %2 leaders, but should be only one")
                                  .arg(team->getTeamName())
                                  .arg(foundLeaders);
            I(message);
            emit this->configureDataValidationFailed(message);
            return;
        }
    }

    emit this->configureDataValidatedCorrectly();
}

void Event::validateConfigureSecondPhaseData()
{
    Personalization *p = Personalization::getInstance();

    /// check if 4 teams was registered
    int teamsCount = m_teams[m_phase].size();
    int requiredTeamsCount = p->getRequiredTeamsCount()/2;
    if(teamsCount != requiredTeamsCount)
    {
        /// less or more than 8 teams
        QString message = tr("Event requires %1 teams").arg(requiredTeamsCount);
        I(message);
        emit this->configureDataValidationFailed(message);
        return;
    }

    /// check data for teams:
    for(Team *team : m_teams[m_phase])
    {
        /// check if team has at least 6 players
        int playersCount = team->getPlayers().size();
        if(playersCount < p->getMinimumPlayersInTeam())
        {
            /// team has least than 6 players
            QString message = tr("Team %1 has less than %2 players")
                                  .arg(team->getTeamName())
                                  .arg(p->getMinimumPlayersInTeam());
            I(message);
            emit this->configureDataValidationFailed(message);
            return;
        }

        /// check if team has both genders
        bool foundMale = false;
        bool foundFemale = false;
        for(Player *player : team->getPlayers())
        {
            if(player->getGender() == Player::Gender::Male)
                foundMale = true;

            if(player->getGender() == Player::Gender::Female)
                foundFemale = true;
        }
        if(!foundMale || !foundFemale)
        {
            /// one gender is missing in team
            QString message = tr("Team %1 doesn't contain players of either gender")
                                  .arg(team->getTeamName());
            I(message);
            emit this->configureDataValidationFailed(message);
            return;
        }

        /// check if team has a junior
        if(p->getRequiresJuniors())
        {
            bool foundJunior = false;
            for(Player *player : team->getPlayers())
            {
                if(player->getAgeGroup() == Player::AgeGroup::Junior)
                {
                    foundJunior = true;
                    break;
                }
            }

            if(!foundJunior)
            {
                /// junior player is missing in team
                QString message = tr("Team %1 doesn't contain any junior player")
                                      .arg(team->getTeamName());
                I(message);
                emit this->configureDataValidationFailed(message);
                return;
            }
        }

        /// check if team has one leader
        int foundLeaders = 0;
        for(Player *player : team->getPlayers())
        {
            if(player->getIsTeamLeader())
                ++ foundLeaders;
        }
        if(foundLeaders == 0)
        {
            /// team missing leader
            QString message = tr("In team %1, no leader was selected, each team requires leader")
                                  .arg(team->getTeamName());
            I(message);
            emit this->configureDataValidationFailed(message);
            return;
        }
        else if(foundLeaders > 1)
        {
            /// team contains few leaders
            QString message = tr("Team %1 has %2 leaders, but should be only one")
                                  .arg(team->getTeamName())
                                  .arg(foundLeaders);
            I(message);
            emit this->configureDataValidationFailed(message);
            return;
        }
    }

    emit this->configureDataValidatedCorrectly();
}

uint Event::generateUniqueTeamID() const
{
    uint loopCounter = 0;
    constexpr uint loopLimit = 10'000;

    bool foundUnique = false;
    uint rndID;
    do
    {
        rndID = QRandomGenerator::global()->generate() % 1'000'000;

        /// test if that ID in teams exist
        foundUnique = this->isTeamIDUniqueInTeamssList(rndID);

        if(++loopCounter > loopLimit)
        {
            W("Loop limit activated (" + QString::number(loopLimit) +
              " iterations)! Random unique TeamID might not be unique")
            break;
        }
    }
    while(!foundUnique && rndID != 0);

    return rndID;
}

bool Event::isTeamIDUniqueInTeamssList(uint id) const
{
    for(Team *t : m_teams[m_phase])
    {
        if(t->getTeamID() == id)
        {
            /// found identical ID
            return false;
        }
    }
    return true;
}

void Event::copyPlayersFromFirstToSecondPhase()
{
    W("function not finished - selecting only first 4 players")
    const TeamList &teamsPhase1 = m_teams[Phase::First];
    TeamList &teamsPhase2 = m_teams[Phase::Second];

    if(teamsPhase1.size() < 4)
    {
        W("Cannot copy teams from phase1 to phase2 - phase1 teamList contain only "
          +QString::number(teamsPhase1.size())+" teams, required at least 4")
        return;
    }

    for(int i=0; i<4; i++)
    {
        Team *teamPhase1 = teamsPhase1[i];
        this->createDetachedTeam();
        Team *teamPhase2 = m_detachedTeam;
        teamPhase2->copyFromOtherTeam(*teamPhase1);
        this->addTeamUsingDetachedTeam();
    }
}

const TeamList &Event::getTeams() const
{
    return m_teams[m_phase];
}

Team *Event::getDetachedTeam() const
{
    return m_detachedTeam;
}

Event::Phase Event::getPhase() const
{
    return m_phase;
}

const QString &Event::getName() const
{
    return m_name;
}

const QString &Event::getDate(int phase) const
{
    if(phase != Phase::First && phase != Phase::Second)
        return m_date[m_phase];
    return m_date[phase];
}

const QString &Event::getCompetitionOrganizer() const
{
    return m_competitionOrganizer;
}

const QString &Event::getFirstPhasePlace() const
{
    return m_firstPhasePlace;
}

const QString &Event::getSecondPhasePlace() const
{
    return m_secondPhasePlace;
}

const QStringList &Event::getJudges() const
{
    return m_judges;
}

const QString &Event::getUnionDelegate() const
{
    return m_unionDelegate;
}

Event::Stage Event::getStage() const
{
    return m_stage;
}

int Event::getRound() const
{
    return m_round;
}

Event::RoundStage Event::getRoundStage() const
{
    return m_roundStage;
}

Match *Event::getMatch() const
{
    if(m_matches[m_phase].size() < m_round || m_round < 1)
    {
        W(QString::asprintf("matches size {%lld} <= m_round {%d-1}, cannot return match", m_matches[m_phase].size(), m_round));
        return nullptr;
    }
    return m_matches[m_phase][m_round-1];
}

const MatchList &Event::getMatches() const
{
    return m_matches[m_phase];
}

void Event::setPhase(Phase phase)
{
    if (m_phase == phase)
        return;
    m_phase = phase;
    emit phaseChanged();
}

void Event::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}

void Event::setDate(const QString &date, int phase)
{
    QString *pm_date;
    if(phase != Phase::First && phase != Phase::Second)
        pm_date = &(m_date[m_phase]);
    else
        pm_date = &(m_date[phase]);

    if (*pm_date == date)
        return;
    *pm_date = date;
    emit dateChanged();
}

void Event::setCompetitionOrganizer(const QString &competitionOrganizer)
{
    if (m_competitionOrganizer == competitionOrganizer)
        return;
    m_competitionOrganizer = competitionOrganizer;
    emit competitionOrganizerChanged();
}

void Event::setFirstPhasePlace(const QString &firstPhasePlace)
{
    if (m_firstPhasePlace == firstPhasePlace)
        return;
    m_firstPhasePlace = firstPhasePlace;
    emit firstPhasePlaceChanged();
}

void Event::setSecondPhasePlace(const QString &secondPhasePlace)
{
    if (m_secondPhasePlace == secondPhasePlace)
        return;
    m_secondPhasePlace = secondPhasePlace;
    emit secondPhasePlaceChanged();
}

void Event::setJudges(const QStringList &judges)
{
    if (m_judges == judges)
        return;
    m_judges = judges;
    emit judgesChanged();
}

void Event::setUnionDelegate(const QString &unionDelegate)
{
    if (m_unionDelegate == unionDelegate)
        return;
    m_unionDelegate = unionDelegate;
    emit unionDelegateChanged();
}

void Event::setStage(Stage stage)
{
    if(m_stage == stage)
        return;
    m_stage = stage;
    emit stageChanged();
}

void Event::setRound(int round)
{
    if (m_round == round)
        return;
    m_round = round;
    emit roundChanged();
}

void Event::setRoundStage(RoundStage roundStage)
{
    if (m_roundStage == roundStage)
        return;
    m_roundStage = roundStage;
    emit roundStageChanged();
}

TeamList &Event::getTeamsP1()
{
    return m_teams[Phase::First];
}

TeamList &Event::getTeamsP2()
{
    return m_teams[Phase::Second];
}

MatchList &Event::getMatchesP1()
{
    return m_matches[Phase::First];
}

MatchList &Event::getMatchesP2()
{
    return m_matches[Phase::Second];
}
