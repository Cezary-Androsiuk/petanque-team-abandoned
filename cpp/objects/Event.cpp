#include "Event.h"

Event::Event(QObject *parent)
    : QObject{parent}
    , m_detachedTeam(nullptr)
    , m_phase(1)
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
    // I("Creating detached Team")
    if(m_detachedTeam != nullptr)
    {
        W("Creating new detached Team, while old wasn't deleted")
    }

    m_detachedTeam = new Team(this);
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
    team->setTeamID( this->generateUniqueTeamID() );
    emit this->detachedTeamUsed();

    m_teams.append(team);
    emit this->teamsChanged();
}

uint Event::generateUniqueTeamID() const
{
    uint loopCounter = 0;
    constexpr uint loopLimit = 10'000;

    bool foundUnique = false;
    uint rnd;
    do
    {
        rnd = QRandomGenerator::global()->generate();

        /// test if that ID in teams exist
        foundUnique = true; /// assume is unique
        for(Team *t : m_teams)
        {
            if(t->getTeamID() == rnd)
            {
                /// found identical ID
                foundUnique = false;
                break;
            }
        }

        if(++loopCounter > loopLimit)
        {
            W("Loop limit activated (" + QString::number(loopLimit) +
              " iterations)! Random unique TeamID might not be unique")
            break;
        }
    }
    while(!foundUnique);

    return rnd;
}

int Event::getPhase() const
{
    return m_phase;
}

TeamList Event::getTeams() const
{
    return m_teams;
}

Team *Event::getDetachedTeam() const
{
    return m_detachedTeam;
}

void Event::setPhase(int phase)
{
    if (m_phase == phase)
        return;
    m_phase = phase;
    emit phaseChanged();
}
