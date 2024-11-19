#ifndef MATCHTYPEBASE_H
#define MATCHTYPEBASE_H

#include <QObject>
#include <QVector>

#include "cpp/support/Log.h"
#include "cpp/objects/Player.h"

typedef QVector<QVector<bool>> BoolMatrix;
typedef QVector<PlayerList> GroupsOfPlayersLists;

class MatchTypeBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BoolMatrix selection READ getSelection NOTIFY selectionChanged FINAL)
    Q_PROPERTY(uint rows READ getRows CONSTANT FINAL)
    Q_PROPERTY(uint columns READ getColumns CONSTANT FINAL)
    Q_PROPERTY(GroupsOfPlayersLists usedPlayersInGroups READ getUsedPlayersInGroups NOTIFY usedPlayersInGroupsChanged FINAL)

public:
    explicit MatchTypeBase(uint playersCount, uint groups, QObject *parent = nullptr);

    virtual bool isSelectionDataValid(QString *message = nullptr) const = 0;

protected:
    bool isSelectionDataValid(const int minSelections, const int maxSelections, QString *message) const;
    void countSelectionsInGroups(QVector<int> &groups) const;

public slots:
    void setSelectionCell(uint row, uint column, bool value);
    void computePlayersUsed(const PlayerList &players); /// should be used after selection

public:
    const BoolMatrix &getSelection() const;
    uint getRows() const;
    uint getColumns() const;
    GroupsOfPlayersLists getUsedPlayersInGroups() const;

signals:
    void selectionChanged();

    void usedPlayersInGroupsChanged();

protected:
    const uint m_rows; // players
    const uint m_columns; // groups
    BoolMatrix m_selection; // rows<columns> [row][col]

    GroupsOfPlayersLists m_usedPlayersInGroups;
};

#endif // MATCHTYPEBASE_H
