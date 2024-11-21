#ifndef MATCHTYPEBASE_H
#define MATCHTYPEBASE_H

#include <QObject>
#include <QVector>

#include "cpp/support/Log.h"
#include "cpp/objects/Player.h"

typedef QVector<QVector<bool>> BoolMatrix;
typedef QVector<QVector<int>> IntMatrix;
typedef QVector<PlayerList> GroupsOfPlayersLists;

class MatchTypeBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BoolMatrix selection READ getSelection NOTIFY selectionChanged FINAL)
    Q_PROPERTY(uint rows READ getRows CONSTANT FINAL)
    Q_PROPERTY(uint columns READ getColumns CONSTANT FINAL)
    Q_PROPERTY(uint playersCount READ getPlayersCount CONSTANT FINAL)
    Q_PROPERTY(uint groupsCount READ getGroupsCount CONSTANT FINAL)
    Q_PROPERTY(GroupsOfPlayersLists usedPlayersInGroups READ getUsedPlayersInGroups NOTIFY usedPlayersInGroupsChanged FINAL)

public:
    explicit MatchTypeBase(uint playersCount, uint groups, QObject *parent = nullptr);

    virtual bool isSelectionDataValid(QString *message = nullptr) const = 0;

protected:
    bool isSelectionDataValid(const int rangeOfPlayersCountInGroup[2], QString *message) const;
    void countSelectionsInGroups(QVector<int> &groups) const;

public slots:
    void setSelectionCell(uint row, uint column, bool value);
    void computePlayersUsed(const PlayerList &players); /// should be used after selection

public:
    const BoolMatrix &getSelection() const;
    uint getRows() const;
    uint getPlayersCount() const;
    uint getColumns() const;
    uint getGroupsCount() const;
    GroupsOfPlayersLists getUsedPlayersInGroups() const;

signals:
    void selectionChanged();

    void usedPlayersInGroupsChanged();

protected:
    const uint m_rows; // players
    const uint &m_playersCount; // = m_rows

    const uint m_columns; // groups
    const uint &m_groupsCount; // = m_columns

    BoolMatrix m_selection; // rows<columns> [row][col]
    IntMatrix m_points; // rows<coulumns> []

    GroupsOfPlayersLists m_usedPlayersInGroups;
};

#endif // MATCHTYPEBASE_H
