#ifndef MATCHPOINTS_H
#define MATCHPOINTS_H

#include <QObject>
#include <QVector>

#include "cpp/support/Log.h"

typedef QVector<int> IntVector;

class MatchPoints : public QObject
{
    Q_OBJECT
    Q_PROPERTY(IntVector points READ getPoints NOTIFY pointsChanged() FINAL)
    Q_PROPERTY(uint groupsCount READ getGroupsCount CONSTANT FINAL)

public:
    explicit MatchPoints(uint groupsCount, QObject *parent = nullptr);

public:
    bool isDataValid(QString *message) const;

public slots:
    void setPointsForGroup(uint groupIndex, int value);

public:
    const IntVector &getPoints() const;
    uint getGroupsCount() const;

signals:
    void pointsChanged();

private:

    const uint m_groupsCount;
    IntVector m_points; // [groupsCount]
};

#endif // MATCHPOINTS_H
