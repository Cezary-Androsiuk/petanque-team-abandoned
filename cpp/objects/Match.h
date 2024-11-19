#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QList>
#include <QPair>

#include "cpp/objects/MatchTeam.h"
#include "cpp/objects/Team.h"

class Match : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MatchTeamList matchTeams READ getMatchTeams NOTIFY matchTeamsChanged FINAL)
    Q_PROPERTY(TeamList teamsRefList READ getTeamsRefList CONSTANT FINAL)

public:
    explicit Match(QObject *parent = nullptr);

    void addMatchTeam(MatchTeam *matchTeam);
    void addMatchCombination(int teamIndex1, int teamIndex2);

public:
    const MatchTeamList &getMatchTeams() const;
    const QList<QPair<int, int>> &getMatchCombinations() const;

public slots:
    Team *getTeamByIndexes(const TeamList &teams, int combinationIndex, int teamIndex);

signals:
    void matchTeamsChanged();

private:
    MatchTeamList m_matchTeams;
    QList<QPair<int, int>> m_matchCombinations;
};

typedef QList<Match*> MatchList;

#endif // MATCH_H
