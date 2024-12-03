#include "Team.h"

Team::Team(QObject *parent)
    : QObject{parent}
    , m_teamID(0)
    , m_detachedPlayer(nullptr)
{
}

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
    // I("Using other Team as a reference")
    if(this == &team)
        return;

    /// NOTE! THIS NOT COPY TEAM ID
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
    // I("Creating detached Player")
    if(m_detachedPlayer != nullptr)
    {
        W("Creating new detached Player, while old wasn't deleted")
    }

    m_detachedPlayer = new Player(this);
    m_detachedPlayer->setPlayerID( this->generateUniquePlayerID() );
    emit this->detachedPlayerChanged();
}

void Team::deleteDetachedPlayer()
{
    // I("Deleting detached Player")
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
    // I("Adding detached Player to Team")
    Player *player = m_detachedPlayer;
    m_detachedPlayer = nullptr;

    if(!this->isPlayerIDUniqueInPlayersList( player->getPlayerID() ))
        W("In the meantime creating detached Player, playerID was changed to not unique (in relation to players list)");

    m_players.append(player);
    emit this->playersChanged();
}

void Team::deletePlayer(const Player * const player)
{
    int index = -1;
    for(int i=0; i<m_players.size(); i++)
    {
        if(player == m_players[i])
        {
            index = i;
        }
    }

    if(index == -1)
    {
        W(QString::asprintf("Player to delete %p was not found!", player))
        return;
    }

    delete m_players[index];
    m_players.remove(index);

    emit this->playersChanged();
}

void Team::uncheckAllLeaders()
{
    for(auto &player : m_players)
        player->setIsTeamLeader(false);
}

uint Team::generateUniquePlayerID() const
{
    uint loopCounter = 0;
    constexpr uint loopLimit = 10'000;

    bool foundUnique = false;
    uint rndID;
    do
    {
        rndID = QRandomGenerator::global()->generate() % 1'000'000;

        /// test if that ID in this team players exist
        foundUnique = this->isPlayerIDUniqueInPlayersList(rndID);

        if(++loopCounter > loopLimit)
        {
            W("Loop limit activated (" + QString::number(loopLimit) +
              " iterations)! Random unique PlayerID might not be unique in this team")
            break;
        }
    }
    while(!foundUnique && rndID != 0);

    return rndID;
}

bool Team::isPlayerIDUniqueInPlayersList(uint id) const
{
    for(Player *p : m_players)
    {
        if(p->getPlayerID() == id)
        {
            /// found identical ID
            return false;
        }
    }
    return true;
}

uint Team::getTeamID() const
{
    return m_teamID;
}

QString Team::getTeamName() const
{
    return m_teamName;
}

PlayerList Team::getPlayers() const
{
    return m_players;
}

Player *Team::getDetachedPlayer() const
{
    return m_detachedPlayer;
}

void Team::setTeamID(uint teamID)
{
    m_teamID = teamID;
}

void Team::setTeamName(const QString &teamName)
{
    if (m_teamName == teamName)
        return;
    m_teamName = teamName;
    emit this->teamNameChanged();
}
