#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QList>

#include "cpp/support/Log.h"
#include "cpp/objects/Team.h"

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<Team *> teams READ getTeams NOTIFY teamsChanged FINAL)

public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();
    QList<Team *> getTeams() const;
    void setTeams(const QList<Team *> &teams);

public slots:
    Team *addEmptyTeam();
    void removeLastTeam();

signals:

    void teamsChanged();

private:
    QList<Team*> m_teams;
};

#endif // BACKEND_H
