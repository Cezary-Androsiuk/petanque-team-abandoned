#ifndef MATCHDUBLETS_H
#define MATCHDUBLETS_H

#include <QObject>
#include <QVector>

#include "cpp/support/Log.h"

typedef QVector<QVector<bool>> BoolMatrix;

class MatchDublets : public QObject
{
    Q_OBJECT
public:
    explicit MatchDublets(int playersCount, QObject *parent = nullptr);

signals:

private:
    QVector<QVector<bool>> m_selection; // rows<columns> [row][col]
};

#endif // MATCHDUBLETS_H
