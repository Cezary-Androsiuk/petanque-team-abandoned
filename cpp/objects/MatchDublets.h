#ifndef MATCHDUBLETS_H
#define MATCHDUBLETS_H

#include <QObject>
#include <QList>

#include "cpp/support/Log.h"

class MatchDublets : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<uint> playersID READ getPlayersID NOTIFY playersIDChanged FINAL)
public:
    explicit MatchDublets(QObject *parent = nullptr);

    const QList<uint> &getPlayersID() const;
    void addPlayerID(uint playerID);

signals:
    void playersIDChanged();

private:
    QList<uint> m_playersID;
};

#endif // MATCHDUBLETS_H
