#include "MatchTypeBase.h"

MatchTypeBase::MatchTypeBase(uint playersCount, uint groups, QObject *parent)
    : QObject{parent}
    , m_selection{new Selection(playersCount, groups, this)}
    , m_matchPoints{new MatchPoints(playersCount, this)}
    , m_usedPlayersInGroups(groups, PlayerList())
{}

bool MatchTypeBase::_isSelectionDataValid(const int rangeOfPlayersCountInGroup[2], QString *message) const
{
    return m_selection->isDataValid(rangeOfPlayersCountInGroup, message);
}

bool MatchTypeBase::_isMatchPointsDataValid(QString *message) const
{
    return m_matchPoints->isDataValid(message);
}

void MatchTypeBase::computePlayersUsed(const PlayerList &players)
{
    if(!isSelectionDataValid())
    {
        I("Skipping computing used players, due to invalid data");
        return;
    }

    uint rows = m_selection->getPlayersCount();
    uint columns = m_selection->getGroupsCount();
    if(players.size() != rows)
    {
        W("players size(" + QString::number(players.size()) + ") is not equal to count of rows(" + QString::number(rows) + ")");
        return;
    }

    /// clear usedPlayersInGroups
    for(int i=0; i<columns; i++)
    {
        for(Player *p : m_usedPlayersInGroups[i])
            delete p;
        m_usedPlayersInGroups[i].clear();
    }

    /// create and add player to list coresponding to group
    for(int i=0; i<columns; i++)
    {
        for(int j=0; j<rows; j++)
        {
            if(!m_selection->getValues()[j][i])
                continue;

            Player *player = players[j];
            Player *newPlayer = new Player(this);
            newPlayer->copyFromOtherPlayer(*player);
            m_usedPlayersInGroups[i].append(newPlayer);
            /*
             * Now use copy of the value, but now I find out that I can use
             * std::shared_ptr or QSharedPointer in team along with std::weak_ptr or QWeakPointer
             * and verification if weak pointer exist before use
            */
        }
    }
    emit this->usedPlayersInGroupsChanged();
}

Selection *MatchTypeBase::getSelection() const
{
    return m_selection;
}

MatchPoints *MatchTypeBase::getMatchPoints() const
{
    return m_matchPoints;
}

GroupsOfPlayersLists MatchTypeBase::getUsedPlayersInGroups() const
{
    return m_usedPlayersInGroups;
}
