#include "Match.h"

Match::Match(QObject *parent)
    : QObject{parent}
{}

void Match::addMatchTeam(MatchTeam *matchTeam)
{
    m_matchTeams.append(matchTeam);
    emit this->matchTeamsChanged();
}

void Match::addMatchCombination(int teamIndex1, int teamIndex2)
{
    m_matchCombinations.emplace(teamIndex1, teamIndex2);
}

const MatchTeamList &Match::getMatchTeams() const
{
    return m_matchTeams;
}

const QList<QPair<int, int>> &Match::getMatchCombinations() const
{
    return m_matchCombinations;
}

Team *Match::getTeamByIndexes(const TeamList &teams, int combinationIndex, int teamIndex)
{
    if(teams.empty())
    {
        E("teams is empty");
        return nullptr;
    }

    if(combinationIndex != m_matchCombinations.size())
    {
        auto a = QString::number(combinationIndex);
        auto b = QString::number(m_matchCombinations.size());
        W("input combinationIndex("+ a +") != m_matchCombinations.size()("+ b +"), returning value on index 0");
        return teams[0];
    }

    if(teamIndex != 1 && teamIndex != 2)
    {
        auto a = QString::number(teamIndex);
        W("teamIndex is "+ a +", not 1 or 2, returning value on index 0");
        return teams[0];
    }

    int index;
    if(teamIndex == 1)
        index = m_matchCombinations[combinationIndex].first;
    else
        index = m_matchCombinations[combinationIndex].second;
    if(teams.size() <= index)
    {
        auto a = QString::number(teams.size());
        auto b = QString::number(m_matchCombinations.size());
        W("teams size is " + a + " and index is " + b + " - cannot read that team, returning value on index 0");
        return teams[0];
    }

    return teams[index];
}
