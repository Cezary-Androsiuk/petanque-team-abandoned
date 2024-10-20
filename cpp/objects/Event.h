#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QList>

#include "cpp/support/Log.h"
#include "cpp/objects/Team.h"

class Event : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TeamList teams READ getTeams NOTIFY teamsChanged FINAL)
    Q_PROPERTY(Team* detachedTeam READ getDetachedTeam NOTIFY detachedTeamChanged FINAL)

public:
    explicit Event(QObject *parent = nullptr);
    ~Event();
    void clearTeams();

public slots:
    void createDetachedTeam();
    void deleteDetachedTeam();

    void addTeamUsingDetachedTeam();

public:
    TeamList getTeams() const;
    Team *getDetachedTeam() const;

signals:
    void teamsChanged();
    void detachedTeamChanged();

    void detachedTeamUsed();

private:
    TeamList m_teams;
    Team *m_detachedTeam;
};

#endif // EVENT_H
