#ifndef MATCHTRIPLETS_H
#define MATCHTRIPLETS_H

#include <QObject>
#include <QList>

#include "cpp/support/Log.h"

class MatchTriplets : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<uint> playersID READ getPlayersID NOTIFY playersIDChanged FINAL)
public:
    explicit MatchTriplets(QObject *parent = nullptr);

    const QList<uint> &getPlayersID() const;
    void addPlayerID(uint playerID);

signals:
    void playersIDChanged();

private:
    QList<uint> m_playersID;
};

#endif // MATCHTRIPLETS_H
