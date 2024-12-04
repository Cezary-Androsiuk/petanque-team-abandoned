#ifndef MATCHPOINTS_H
#define MATCHPOINTS_H

#include <QObject>
#include <QVector>

#include "cpp/support/Log.h"
#include "cpp/objects/Player.h"

typedef QVector<int> IntVector;
typedef QVector<PlayerList> GroupsOfPlayersLists;

class MatchPoints : public QObject
{
    Q_OBJECT
    Q_PROPERTY(IntVector points READ getPoints NOTIFY pointsChanged() FINAL)
    Q_PROPERTY(uint groupsCount READ getGroupsCount CONSTANT FINAL)
    Q_PROPERTY(GroupsOfPlayersLists usedPlayersInGroups READ getUsedPlayersInGroups NOTIFY usedPlayersInGroupsChanged FINAL)

public:
    explicit MatchPoints(uint groupsCount, QObject *parent = nullptr);

public:
    bool isDataValid(QString *message) const;

public slots:
    void setPointsForGroup(uint groupIndex, int value);

public:
    const IntVector &getPoints() const;
    uint getGroupsCount() const;
    const GroupsOfPlayersLists &getUsedPlayersInGroups() const;

    void setUsedPlayersInGroups(const GroupsOfPlayersLists &usedPlayersInGroups);

signals:
    void pointsChanged();
    void usedPlayersInGroupsChanged();

private:
    const uint m_groupsCount;
    IntVector m_points; // [groupsCount]
    GroupsOfPlayersLists m_usedPlayersInGroups;// [groupsCount]
};

#endif // MATCHPOINTS_H
