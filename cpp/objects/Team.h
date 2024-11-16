#ifndef TEAM_H
#define TEAM_H

#include <QObject>
#include <QList>
#include <QRandomGenerator>

#include "cpp/support/Log.h"
#include "cpp/objects/Player.h"

class Team : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint teamID              READ getTeamID                              CONSTANT                        FINAL)
    Q_PROPERTY(QString teamName         READ getTeamName        WRITE setTeamName   NOTIFY teamNameChanged          FINAL)
    Q_PROPERTY(PlayerList players       READ getPlayers                             NOTIFY playersChanged           FINAL)
    Q_PROPERTY(Player * detachedPlayer  READ getDetachedPlayer                      NOTIFY detachedPlayerChanged    FINAL)

public:
    explicit Team(QObject *parent = nullptr);
    ~Team();
    void clearPlayers();

public slots:
    void createDetachedPlayer();
    void deleteDetachedPlayer();

    void addPlayerUsingDetachedPlayer();
    void deletePlayer(const Player *const player);

    void uncheckAllLeaders();

private:
    uint generateUniquePlayerID() const;
    bool isPlayerIDUniqueInPlayersList(uint id) const;

public:
    uint getTeamID() const;
    QString getTeamName() const;
    PlayerList getPlayers() const;
    Player *getDetachedPlayer() const;

    void setTeamID(uint teamID);
    void setTeamName(const QString &teamName);

signals:
    void teamNameChanged();
    void playersChanged();
    void detachedPlayerChanged();

private:
    uint m_teamID; // unique in event
    QString m_teamName;

    PlayerList m_players;
    Player *m_detachedPlayer;
};

typedef QList<Team*> TeamList;

#endif // TEAM_H
