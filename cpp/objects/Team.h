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
    Q_PROPERTY(PlayerList players READ getPlayers NOTIFY playersChanged FINAL)
    Q_PROPERTY(qsizetype playersCount READ getPlayersCount NOTIFY playersChanged FINAL)
    Q_PROPERTY(Player * detachedPlayer READ getDetachedPlayer NOTIFY detachedPlayerChanged FINAL)

public:
    explicit Team(QObject *parent = nullptr);
    ~Team();
    void clearPlayers();
    void copyFromOtherTeam(const Team &team);

public slots:
    void createDetachedPlayer();
    void deleteDetachedPlayer();

    void addPlayerUsingDetachedPlayer();

public:
    QString getTeamName() const;

    PlayerList getPlayers() const;
    qsizetype getPlayersCount() const; // used by qml to extend list
    Player *getDetachedPlayer() const;

    void setTeamName(const QString &teamName);

signals:
    void teamNameChanged();
    void playersChanged();
    void detachedPlayerChanged();

    void detachedPlayerUsed();

private:
    QString m_teamName;

    PlayerList m_players;
    Player *m_detachedPlayer;
};

typedef QList<Team*> TeamList;

#endif // TEAM_H
