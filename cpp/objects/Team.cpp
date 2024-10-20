#include "Team.h"

Team::Team(QObject *parent)
    : QObject{parent}
    , m_detachedPlayer(nullptr)
{}

Team::~Team()
{
    this->clearPlayers();
}

void Team::clearPlayers()
{
    for(Player *player : m_players)
        delete player;
    m_players.clear();
}

void Team::copyFromOtherTeam(const Team &team)
{
    I("Using other team as a reference")

    if(this == &team)
        return;

    this->setTeamName(team.getTeamName());

    this->clearPlayers();
    for(Player *player : team.getPlayers())
    {
        Player *newPlayer = new Player(this);
        newPlayer->copyFromOtherPlayer(*player);
        m_players.append(newPlayer);
    }
    emit this->playersChanged();

}

void Team::createDetachedPlayer()
{
    I("Creating detached Player")
    if(m_detachedPlayer != nullptr)
    {
        W("Creating new detached Player, while old wasn't deleted")
    }

    m_detachedPlayer = new Player(this);
    m_detachedPlayer->setFname("player f name");
    m_detachedPlayer->setLname("player l name");
    emit this->detachedPlayerChanged();
}

void Team::deleteDetachedPlayer()
{
    I("Deleting detached Player")
    if(m_detachedPlayer == nullptr)
    {
        E("trying to delete aleady deleted detached Player")
        return;
    }

    delete m_detachedPlayer;
    m_detachedPlayer = nullptr;
    // emit this->detachedPlayerChanged();
}

void Team::addPlayerUsingDetachedPlayer()
{
    I("Adding detached Player to Team")
    Player *player = new Player(this);

    player->copyFromOtherPlayer(*m_detachedPlayer);
    emit this->detachedPlayerUsed();

    m_players.append(player);
    emit this->playersChanged();
}

QString Team::getTeamName() const
{
    return m_teamName;
}

PlayerList Team::getPlayers() const
{
    return m_players;
}

qsizetype Team::getPlayersCount() const
{
    return m_players.size();
}

Player *Team::getDetachedPlayer() const
{
    return m_detachedPlayer;
}

void Team::setTeamName(const QString &teamName)
{
    if (m_teamName == teamName)
        return;
    m_teamName = teamName;
    emit this->teamNameChanged();
}
