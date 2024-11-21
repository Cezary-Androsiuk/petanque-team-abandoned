#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QList>
#include <QPair>

#include "cpp/objects/MatchTypes.h"
#include "cpp/objects/Team.h"

typedef QList<QPair<int, int>> IntMap;

class Match : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MatchTypesList matchTypesList READ getMatchTypesList NOTIFY matchTypesListChanged FINAL)
    Q_PROPERTY(IntMap matchCombinations READ getMatchCombinations CONSTANT FINAL)

public:
    explicit Match(QObject *parent = nullptr);

    void addMatchTypes(MatchTypes *matchTypes);
    void addMatchCombination(int teamIndex1, int teamIndex2);

public:
    const MatchTypesList &getMatchTypesList() const;
    const IntMap &getMatchCombinations() const;

public slots:
    /// Returns one Team from given list of the teams that is used in the combination(combinationIndex)
    /// and is one from two teams in that combination (teamIndex, first or second)
    /// Returns teams[ m_matchCombinations[combinationIndex][teamIndex] ] value where combination is a matrix
    Team *getTeamByIndexes(const TeamList &teams, int combinationIndex, int teamIndex);

    /// Returns one MatchTypes that is used in the combination(combinationIndex)
    /// and is one from two teams in that combination (teamIndex, first or second)
    /// Returns m_m_matchTypes[ m_matchCombinations[combinationIndex][teamIndex] ] value where combination is a matrix
    MatchTypes *getMatchTypesByIndexes(int combinationIndex, int teamIndex);

signals:
    void matchTypesListChanged();

private:
    MatchTypesList m_matchTypesList;
    IntMap m_matchCombinations;
};

typedef QList<Match*> MatchList;

#endif // MATCH_H
