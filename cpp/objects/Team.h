#ifndef TEAM_H
#define TEAM_H

#include <QObject>
#include <QList>

#include "cpp/support/Log.h"
#include "cpp/objects/Player.h"

class Team : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString teamName READ getTeamName WRITE setTeamName NOTIFY teamNameChanged FINAL)
    Q_PROPERTY(QList<Player *> players READ getPlayers WRITE setPlayers NOTIFY playersChanged FINAL)

public:
    explicit Team(QObject *parent = nullptr);
    ~Team();

    void addPlayer(const Player &player);
    void removePlayer(size_t index);

    QString getTeamName() const;
    QList<Player *> getPlayers() const;
    QList<Player *> * const getPlayersPtr();

    void setTeamName(const QString &teamName);
    void setPlayers(const QList<Player *> &players);

signals:
    void teamNameChanged();

    void playersChanged();

private:
    QString m_teamName;

    QList<Player*> m_players;
};

#endif // TEAM_H
