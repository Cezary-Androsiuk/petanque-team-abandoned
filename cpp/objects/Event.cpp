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

void Event::clearEvent()
{
    this->clearTeams();
    this->setPhase(Event::Phase::First);
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

        matchTeam->setTriplets(triplets);
        matchTeam->setDublets(dublets);
        matchTeam->setSingiels(singiels);

        match->addMatchTeam(matchTeam);
    }
    // D("Match created")

    m_matches[m_phase].append(match);
    return match;
}

void Event::verifyCurrentRoundStage()
{
    const MatchTeamList &mtl = m_matches[m_phase][m_round-1]->getMatchTeamList();
    for(int i=0; i<mtl.size(); i++)
    {
        QString errorMessage;
        bool ok = true;

        switch(m_roundStage)
        {
        case RoundStage::SingielsSelection:
            ok = mtl[i]->getSingiels()->isSelectionDataValid(&errorMessage);
            if(!ok)
            {
                QString returnMessage = tr("in team %1, singiels selection is not valid: %2")
                                            .arg(m_teams[m_phase][i]->getTeamName(), errorMessage);
                I(returnMessage);
                emit this->currentRoundStageVerificationFailed(returnMessage);
                return;
            }

            break;
        case RoundStage::Singiels:

            break;
        case RoundStage::DubletsSelection:
            ok = mtl[i]->getDublets()->isSelectionDataValid(&errorMessage);
            if(!ok)
            {
                QString returnMessage = tr("in team %1, dublets selection is not valid: %2")
                                            .arg(m_teams[m_phase][i]->getTeamName(), errorMessage);
                I(returnMessage);
                emit this->currentRoundStageVerificationFailed(returnMessage);
                return;
            }

            break;
        case RoundStage::Dublets:

            break;
        case RoundStage::TripletsSelection:
            ok = mtl[i]->getTriplets()->isSelectionDataValid(&errorMessage);
            if(!ok)
            {
                QString returnMessage = tr("in team %1, triplets selection is not valid: %2")
                                            .arg(m_teams[m_phase][i]->getTeamName(), errorMessage);
                I(returnMessage);
                emit this->currentRoundStageVerificationFailed(returnMessage);
                return;
            }

            break;
        case RoundStage::Triplets:

            break;
        default:
            W("received unknown round stage: " + QString::number(m_roundStage));
        }


    }
    emit this->currentRoundStageVerified();
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

TeamList Event::getTeams() const
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

QString Event::getName() const
{
    return m_name;
}

QString Event::getFirstPhaseDate() const
{
    return m_firstPhaseDate;
}

QString Event::getSecondPhaseDate() const
{
    return m_secondPhaseDate;
}

QString Event::getCompetitionOrganizer() const
{
    return m_competitionOrganizer;
}

QString Event::getFirstPhasePlace() const
{
    return m_firstPhasePlace;
}

QString Event::getSecondPhasePlace() const
{
    return m_secondPhasePlace;
}

QStringList Event::getJudges() const
{
    return m_judges;
}

QString Event::getUnionDelegate() const
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

MatchList Event::getMatches() const
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

void Event::setFirstPhaseDate(const QString &firstPhaseDate)
{
    if (m_firstPhaseDate == firstPhaseDate)
        return;
    m_firstPhaseDate = firstPhaseDate;
    emit firstPhaseDateChanged();
}

void Event::setSecondPhaseDate(const QString &secondPhaseDate)
{
    if (m_secondPhaseDate == secondPhaseDate)
        return;
    m_secondPhaseDate = secondPhaseDate;
    emit secondPhaseDateChanged();
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
