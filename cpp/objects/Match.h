#ifndef MATCH_H
#define MATCH_H

#include <QObject>
#include <QList>
#include <map>

#include "cpp/objects/MatchTeam.h"

class Match : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MatchTeamList matchTeams READ getMatchTeams NOTIFY matchTeamsChanged FINAL)

public:
    explicit Match(QObject *parent = nullptr);

    void addMatchTeam(MatchTeam *matchTeam);
    void addMatchCombination(int teamIndex1, int teamIndex2);

public:
    const MatchTeamList &getMatchTeams() const;
    const std::map<int, int> &getMatchCombinations() const;

public slots:
    void computeTeamsUsed();

signals:
    void matchTeamsChanged();

private:
    MatchTeamList m_matchTeams;
    std::map<int, int> m_matchCombinations;
};

typedef QList<Match*> MatchList;

#endif // MATCH_H
