#include "Backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}

{
    Team *team;
    Player *player;

    for(int i=0; i<5; i++)
    {
        team = new Team(this);
        team->setTeamName( QString::asprintf("Team %d", i+1) );

        for(int j=0; j<3; j++)
        {
            player = new Player(team);
            player->setFname( QString::asprintf("FirstName(%d %d)", i+1, j+1) );
            player->setLname( QString::asprintf("LastName(%d %d)", i+1, j+1) );
            team->addPlayer(*player);
        }

        m_teams.append(team);
    }
    emit this->teamsChanged();
}

Backend::~Backend()
{
    for(Team *team : m_teams)
        delete team;
    m_teams.clear();
}

QList<Team *> Backend::getTeams() const
{
    return m_teams;
}

Team *Backend::addEmptyTeam()
{
    Team *team;
    team = new Team(this);
    team->setTeamName( QString::asprintf("Team %lld", m_teams.size()) );
    m_teams.append(team);
    emit this->teamsChanged();
    return team;
}

void Backend::removeLastTeam()
{
    Team *team;
    team = m_teams.last();
    delete team;
    m_teams.pop_back();
    emit this->teamsChanged();
}
