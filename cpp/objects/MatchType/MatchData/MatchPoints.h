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
    Q_PROPERTY(uint rows READ getRows CONSTANT FINAL)

public:
    explicit MatchPoints(uint rows, QObject *parent = nullptr);

public:
    bool isDataValid(QString *message) const;

public slots:
    void setPointsForPlayer(uint playerIndex, int value);

public:
    const IntVector &getPoints() const;
    uint getRows() const;

signals:
    void pointsChanged();

private:

    const uint m_rows; // players
    IntVector m_points; // [row]
};

#endif // MATCHPOINTS_H
