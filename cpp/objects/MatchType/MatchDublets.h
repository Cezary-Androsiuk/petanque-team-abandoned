#ifndef MATCHDUBLETS_H
#define MATCHDUBLETS_H

#include <QObject>
#include <QVector>

#include "cpp/support/Log.h"
#include "cpp/objects/MatchType/MatchTypeBase.h"

class MatchDublets : public MatchTypeBase
{
    Q_OBJECT
public:
    explicit MatchDublets(uint playersCount, QObject *parent = nullptr);

signals:

private:
};

#endif // MATCHDUBLETS_H
