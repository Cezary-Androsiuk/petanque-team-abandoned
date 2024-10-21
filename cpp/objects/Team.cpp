#include "Team.h"

Team::Team(QObject *parent)
    : QObject{parent}
    , m_teamID(0)
    , m_detachedPlayer(nullptr)
{
    QObject::connect(this, &Team::detachedPlayerUsed, this, &Team::deleteDetachedPlayer);

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
    Player *player = new Player(this);
    player->copyFromOtherPlayer( *m_detachedPlayer );
    player->setPlayerID( this->generateUniquePlayerID() );
    emit this->detachedPlayerUsed();

    m_players.append(player);
    emit this->playersChanged();
}

uint Team::generateUniquePlayerID() const
{
    uint loopCounter = 0;
    constexpr uint loopLimit = 10'000;

    bool foundUnique = false;
    uint rnd;
    do
    {
        rnd = QRandomGenerator::global()->generate();

        /// test if that ID in this team players exist
        foundUnique = true; /// assume is unique
        for(Player *p : m_players)
        {
            if(p->getPlayerID() == rnd)
            {
                /// found identical ID
                foundUnique = false;
                break;
            }
        }

        if(++loopCounter > loopLimit)
        {
            W("Loop limit activated (" + QString::number(loopLimit) +
              " iterations)! Random unique PlayerID might not be unique in this team")
            break;
        }
    }
    while(!foundUnique);

    return rnd;
}

uint Team::getTeamID() const
{
    D("returnging ID: " + QString::asprintf("%u", m_teamID));
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

qsizetype Team::getPlayersCount() const
{
    return m_players.size();
}

Player *Team::getDetachedPlayer() const
{
    return m_detachedPlayer;
}

void Team::setTeamID(uint teamID)
{
    D("setting ID: " + QString::asprintf("%u", teamID));
    m_teamID = teamID;
}

void Team::setTeamName(const QString &teamName)
{
    if (m_teamName == teamName)
        return;
    m_teamName = teamName;
    emit this->teamNameChanged();
}
