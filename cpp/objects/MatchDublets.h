#ifndef MATCHDUBLETS_H
#define MATCHDUBLETS_H

#include <QObject>
#include <QList>

#include "cpp/support/Log.h"

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
