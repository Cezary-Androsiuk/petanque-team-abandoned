#include "Match.h"

Match::Match(QObject *parent)
    : QObject{parent}
{}

void Match::addMatchTeam(MatchTeam *matchTeam)
{
    m_matchTeamList.append(matchTeam);
    emit this->matchTeamListChanged();
}

void Match::addMatchCombination(int teamIndex1, int teamIndex2)
{
    m_matchCombinations.append(QPair<int, int>(teamIndex1, teamIndex2));
}

const MatchTeamList &Match::getMatchTeamList() const
{
    return m_matchTeamList;
}

const IntMap &Match::getMatchCombinations() const
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

    if(combinationIndex >= m_matchCombinations.size())
    {
        auto a = QString::number(combinationIndex);
        auto b = QString::number(m_matchCombinations.size());
        W("input combinationIndex("+ a +") >= m_matchCombinations.size()("+ b +"), returning value on index 0");
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
        index = m_matchCombinations[combinationIndex].first -1;
    else
        index = m_matchCombinations[combinationIndex].second -1;
    if(teams.size() <= index)
    {
        auto a = QString::number(teams.size());
        auto b = QString::number(index);
        W("teams size is " + a + " and index is " + b + " - cannot read that team, returning value on index 0");
        return teams[0];
    }

    return teams[index];
}

MatchTeam *Match::getMatchTeamByIndexes(int combinationIndex, int teamIndex)
{
    const MatchTeamList &matchTeamList = this->getMatchTeamList();

    if(matchTeamList.empty())
    {
        E("matchTeamList is empty");
        return nullptr;
    }

    if(combinationIndex >= m_matchCombinations.size())
    {
        auto a = QString::number(combinationIndex);
        auto b = QString::number(m_matchCombinations.size());
        W("input combinationIndex("+ a +") >= m_matchCombinations.size()("+ b +"), returning value on index 0");
        return matchTeamList[0];
    }

    if(teamIndex != 1 && teamIndex != 2)
    {
        auto a = QString::number(teamIndex);
        W("teamIndex is "+ a +", not 1 or 2, returning value on index 0");
        return matchTeamList[0];
    }

    int index;
    if(teamIndex == 1)
        index = m_matchCombinations[combinationIndex].first -1;
    else
        index = m_matchCombinations[combinationIndex].second -1;
    if(matchTeamList.size() <= index)
    {
        auto a = QString::number(matchTeamList.size());
        auto b = QString::number(index);
        W("teams size is " + a + " and index is " + b + " - cannot read that team, returning value on index 0");
        return matchTeamList[0];
    }

    return matchTeamList[index];
}
