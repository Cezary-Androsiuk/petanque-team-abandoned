#include "Team.h"

Team::Team(QObject *parent)
    : QObject{parent}
{}

Team::~Team()
{
    for(Player *player : m_players)
        delete player;
    m_players.clear();
}

void Team::addPlayer(const Player &player)
{
    Player *newPlayer = new Player(this);
    newPlayer->fromOtherPlayer(player);
    m_players.append(newPlayer);
}

void Team::removePlayer(size_t index)
{
    if(index > m_players.size()-1)
    {
        W("trying to remove index " + QString::number(index) +
          " while list size is " + QString::number(m_players.size()));
        return;
    }

    Player *rmPlayer = m_players[index];
    delete rmPlayer;
    m_players.remove(index);
}

QString Team::getTeamName() const
{
    return m_teamName;
}

QList<Player *> Team::getPlayers() const
{
    return m_players;
}

QList<Player *> * const Team::getPlayersPtr()
{
    return &m_players;
}

void Team::setTeamName(const QString &teamName)
{
    if (m_teamName == teamName)
        return;
    m_teamName = teamName;
    emit this->teamNameChanged();
}

void Team::setPlayers(const QList<Player *> &players)
{
    if (m_players == players)
        return;
    m_players = players;
    emit this->playersChanged();
}
