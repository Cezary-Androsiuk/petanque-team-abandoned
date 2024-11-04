#include "Match.h"

Match::Match(QObject *parent)
    : QObject{parent}
{}

void Match::addMatchTeam(MatchTeam *matchTeam)
{
    m_matchTeams.append(matchTeam);
    emit this->matchTeamsChanged();
}

MatchTeamList Match::getMatchTeams() const
{
    return m_matchTeams;
}

