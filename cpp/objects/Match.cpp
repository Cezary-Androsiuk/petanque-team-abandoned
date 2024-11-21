#include "Match.h"

Match::Match(QObject *parent)
    : QObject{parent}
{}

void Match::addMatchTypes(MatchTypes *matchTypes)
{
    m_matchTypesList.append(matchTypes);
    emit this->matchTypesListChanged();
}

void Match::addMatchCombination(int teamIndex1, int teamIndex2)
{
    m_matchCombinations.append(QPair<int, int>(teamIndex1, teamIndex2));
}

const MatchTypesList &Match::getMatchTypesList() const
{
    return m_matchTypesList;
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

MatchTypes *Match::getMatchTypesByIndexes(int combinationIndex, int teamIndex)
{
    const MatchTypesList &matchTypesList = this->getMatchTypesList();

    if(matchTypesList.empty())
    {
        E("matchTypesList is empty");
        return nullptr;
    }

    if(combinationIndex >= m_matchCombinations.size())
    {
        auto a = QString::number(combinationIndex);
        auto b = QString::number(m_matchCombinations.size());
        W("input combinationIndex("+ a +") >= m_matchCombinations.size()("+ b +"), returning value on index 0");
        return matchTypesList[0];
    }

    if(teamIndex != 1 && teamIndex != 2)
    {
        auto a = QString::number(teamIndex);
        W("teamIndex is "+ a +", not 1 or 2, returning value on index 0");
        return matchTypesList[0];
    }

    int index;
    if(teamIndex == 1)
        index = m_matchCombinations[combinationIndex].first -1;
    else
        index = m_matchCombinations[combinationIndex].second -1;
    if(matchTypesList.size() <= index)
    {
        auto a = QString::number(matchTypesList.size());
        auto b = QString::number(index);
        W("teams size is " + a + " and index is " + b + " - cannot read that team, returning value on index 0");
        return matchTypesList[0];
    }

    return matchTypesList[index];
}
