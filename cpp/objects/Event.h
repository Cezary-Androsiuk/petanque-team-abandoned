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
    Q_PROPERTY(Phase phase          READ getPhase           WRITE setPhase  NOTIFY phaseChanged         FINAL)

public:
    explicit Event(QObject *parent = nullptr);
    ~Event();
    void clearTeams();
    void clearEvent();

    enum Phase{
        First = 0,
        Second = 1,
    };

public slots:
    void createDetachedTeam();
    void deleteDetachedTeam();

    void addTeamUsingDetachedTeam();
    void deleteTeam(const Team *const team);

private:
    uint generateUniqueTeamID() const;
    bool isTeamIDUniqueInTeamssList(uint id) const;

public:
    Phase getPhase() const;
    TeamList getTeams() const;
    Team *getDetachedTeam() const;

    void setPhase(Phase phase);

signals:
    void teamsChanged();
    void detachedTeamChanged();

    void detachedTeamUsed();

    void phaseChanged();

private:
    Phase m_phase;

    TeamList m_teams[2];
    Team *m_detachedTeam;
};

#endif // EVENT_H
