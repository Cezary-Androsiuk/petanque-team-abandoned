#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QList>

#include "cpp/support/Log.h"

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fname READ getFname WRITE setFname NOTIFY fnameChanged FINAL)
    Q_PROPERTY(QString lname READ getLname WRITE setLname NOTIFY lnameChanged FINAL)
public:
    explicit Player(QObject *parent = nullptr);
    // Player &operator = (const Player &player);
    void copyFromOtherPlayer(const Player &player);

    QString getFname() const;
    QString getLname() const;

    void setFname(const QString &fname);
    void setLname(const QString &lname);

signals:
    void fnameChanged();
    void lnameChanged();

private:
    QString m_fname;
    QString m_lname;
};

typedef QList<Player*> PlayerList;
// typedef const PlayerList &cPlayerList;

#endif // PLAYER_H
