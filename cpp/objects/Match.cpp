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

const std::map<int, int> &Match::getMatchCombinations() const
{
    return m_matchCombinations;
}

void Match::computeTeamsUsed()
{

}
