#include "MatchPoints.h"

MatchPoints::MatchPoints(uint groupsCount, QObject *parent)
    : QObject{parent}
    , m_groupsCount{groupsCount}
    , m_points(groupsCount, 0)
    , m_usedPlayersInGroups(groupsCount, PlayerList())
{}

bool MatchPoints::isDataValid(QString *message) const
{
    return true;
}

void MatchPoints::setPointsForGroup(uint groupIndex, int value)
{
    if(groupIndex >= m_points.size())
    {
        QString pi = QString::number(groupIndex);
        QString ps = QString::number(m_points.size());
        W("given player index("+ pi +") is larger than size of vector(" +ps+ ")");
        return;
    }

    if(m_points[groupIndex] == value)
        return;

    m_points[groupIndex] = value;
    emit this->pointsChanged();
}


const IntVector &MatchPoints::getPoints() const
{
    return m_points;
}

uint MatchPoints::getGroupsCount() const
{
    return m_groupsCount;
}

const GroupsOfPlayersLists &MatchPoints::getUsedPlayersInGroups() const
{
    return m_usedPlayersInGroups;
}

void MatchPoints::setUsedPlayersInGroups(const GroupsOfPlayersLists &usedPlayersInGroups)
{
    for(auto &playersList : m_usedPlayersInGroups)
    {
        for(Player *player :playersList)
            delete player;
        playersList.clear();
    }
    m_usedPlayersInGroups.clear();
    m_usedPlayersInGroups = usedPlayersInGroups;

    emit this->usedPlayersInGroupsChanged();
}
