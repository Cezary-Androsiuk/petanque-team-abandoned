#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QList>
#include <QRandomGenerator>

#include "cpp/support/Log.h"
#include "cpp/objects/Team.h"

class Event : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TeamList teams       READ getTeams                           NOTIFY teamsChanged         FINAL)
    Q_PROPERTY(Team* detachedTeam   READ getDetachedTeam                    NOTIFY detachedTeamChanged  FINAL)
    Q_PROPERTY(int phase            READ getPhase           WRITE setPhase  NOTIFY phaseChanged         FINAL)

public:
    explicit Event(QObject *parent = nullptr);
    ~Event();
    void clearTeams();

public slots:
    void createDetachedTeam();
    void deleteDetachedTeam();

    void addTeamUsingDetachedTeam();

private:
    uint generateUniqueTeamID() const;
    bool isTeamIDUniqueInTeamssList(uint id) const;

public:
    int getPhase() const;
    TeamList getTeams() const;
    Team *getDetachedTeam() const;

    void setPhase(int phase);

signals:
    void teamsChanged();
    void detachedTeamChanged();

    void detachedTeamUsed();

    void phaseChanged();

private:
    int m_phase;

    TeamList m_teams;
    Team *m_detachedTeam;
};

#endif // EVENT_H
