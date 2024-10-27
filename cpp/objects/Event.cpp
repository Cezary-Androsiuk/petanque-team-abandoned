#include "Event.h"

Event::Event(QObject *parent)
    : QObject{parent}
    , m_detachedTeam(nullptr)
    , m_phase(Phase::First)
{
    QObject::connect(this, &Event::detachedTeamUsed, this, &Event::deleteDetachedTeam);
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
    Team *team = new Team(this);
    team->copyFromOtherTeam( *m_detachedTeam );
    if(!this->isTeamIDUniqueInTeamssList( team->getTeamID() ))
        W("In the meantime creating detached Team, teamID{" +
          QString::number(team->getTeamID()) +
          "} was changed to not unique (in relation to teams list)");

    emit this->detachedTeamUsed();

    m_teams[m_phase].append(team);
    emit this->teamsChanged();
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
    while(!foundUnique);

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
