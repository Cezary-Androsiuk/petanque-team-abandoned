#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QList>
#include <QPair>

#include "cpp/objects/MatchTeam.h"
#include "cpp/objects/Team.h"

typedef QList<QPair<int, int>> IntMap;

class Match : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MatchTeamList matchTeamList READ getMatchTeamList NOTIFY matchTeamListChanged FINAL)
    Q_PROPERTY(IntMap matchCombinations READ getMatchCombinations CONSTANT FINAL)

public:
    explicit Match(QObject *parent = nullptr);

    void addMatchTeam(MatchTeam *MatchTeam);
    void addMatchCombination(int teamIndex1, int teamIndex2);

public:
    const MatchTeamList &getMatchTeamList() const;
    const IntMap &getMatchCombinations() const;

public slots:
    /// Returns one Team from given list of the teams that is used in the combination(combinationIndex)
    /// and is one from two teams in that combination (teamIndex, first or second)
    /// Returns teams[ m_matchCombinations[combinationIndex][teamIndex] ] value where combination is a matrix
    Team *getTeamByIndexes(const TeamList &teams, int combinationIndex, int teamIndex);

    /// Returns one MatchTeam that is used in the combination(combinationIndex)
    /// and is one from two teams in that combination (teamIndex, first or second)
    /// Returns m_matchTeam[ m_matchCombinations[combinationIndex][teamIndex] ] value where combination is a matrix
    MatchTeam *getMatchTeamByIndexes(int combinationIndex, int teamIndex);

signals:
    void matchTeamListChanged();

private:
    MatchTeamList m_matchTeamList;
    IntMap m_matchCombinations;
};

typedef QList<Match*> MatchList;

#endif // MATCH_H
