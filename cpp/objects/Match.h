#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QList>

#include "cpp/objects/MatchTeam.h"

class Match : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MatchTeamList matchTeams READ getMatchTeams NOTIFY matchTeamsChanged FINAL)

public:
    explicit Match(QObject *parent = nullptr);

    void addMatchTeam(MatchTeam *matchTeam);

public:
    MatchTeamList getMatchTeams() const;

signals:
    void matchTeamsChanged();

private:
    MatchTeamList m_matchTeams;
};

typedef QList<Match*> MatchList;

#endif // MATCH_H
