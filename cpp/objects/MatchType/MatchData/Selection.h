#ifndef SELECTION_H
#define SELECTION_H

#include <QObject>
#include <QVector>

#include "cpp/support/Log.h"

typedef QVector<QVector<bool>> BoolMatrix;

class Selection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BoolMatrix values READ getValues NOTIFY valuesChanged FINAL)
    Q_PROPERTY(uint playersCount READ getPlayersCount CONSTANT FINAL)
    Q_PROPERTY(uint groupsCount READ getGroupsCount CONSTANT FINAL)

public:
    explicit Selection(uint playersCount, uint groupsCount, QObject *parent = nullptr);

public:
    bool isDataValid(const int rangeOfPlayersCountInGroup[2], QString *message) const;

private:
    void countSelectionsInGroups(QVector<int> &groups) const;

public slots:
    void setValueForCell(uint playerIndex, uint groupsCount, bool value);

public:
    const BoolMatrix &getValues() const;
    uint getPlayersCount() const;
    uint getGroupsCount() const;

signals:
    void valuesChanged();

private:
    const uint m_playersCount; // row
    const uint m_groupsCount; // columns
    BoolMatrix m_values; // playersCount<groupsCount> [playersCount][groupsCount]
};

#endif // SELECTION_H
