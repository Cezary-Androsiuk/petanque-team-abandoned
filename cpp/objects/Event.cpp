#include "Event.h"

Event::Event(QObject *parent)
    : QObject{parent}
    , m_detachedTeam(nullptr)
{
    QObject::connect(this, &Event::detachedTeamUsed, this, &Event::deleteDetachedTeam);

    // Team *team;
    // Player *player;

    // for(int i=0; i<5; i++)
    // {
    //     team = new Team(this);
    //     team->setTeamName( QString::asprintf("Team %d", i+1) );

    //     for(int j=0; j<3; j++)
    //     {
    //         player = new Player(team);
    //         player->setFname( QString::asprintf("FirstName(%d %d)", i+1, j+1) );
    //         player->setLname( QString::asprintf("LastName(%d %d)", i+1, j+1) );
    //         team->addPlayer(*player);
    //     }

    //     m_teams.append(team);
    // }
}

Event::~Event()
{
    this->clearTeams();
}

void Event::clearTeams()
{
    for(Team *team : m_teams)
        delete team;
    m_teams.clear();
}

void Event::createDetachedTeam()
{
    I("Creating detached Team")
    if(m_detachedTeam != nullptr)
    {
        W("Creating new detached Team, while old wasn't deleted")
    }

    m_detachedTeam = new Team(this);
    m_detachedTeam->setTeamName("team name");
    emit this->detachedTeamChanged();
}

void Event::deleteDetachedTeam()
{
    I("Deleting detached Team")
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
    I("Adding detached Team to Event")
    Team *team = new Team(this);

    team->copyFromOtherTeam(*m_detachedTeam);
    emit this->detachedTeamUsed();

    m_teams.append(team);
    emit this->teamsChanged();
}

TeamList Event::getTeams() const
{
    return m_teams;
}

Team *Event::getDetachedTeam() const
{
    return m_detachedTeam;
}
