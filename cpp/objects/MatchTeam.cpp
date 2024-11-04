#include "MatchTeam.h"

MatchTeam::MatchTeam(QObject *parent)
    : QObject{parent}
{}

void MatchTeam::addTriplet(uint playerID[4])
{

}

void MatchTeam::addDublet(uint playerID[3])
{

}

void MatchTeam::addSingiel(uint playerID)
{

}

uint MatchTeam::getTeamID() const
{
    return m_teamID;
}

void MatchTeam::setTeamID(uint teamID)
{
    if (m_teamID == teamID)
        return;
    m_teamID = teamID;
    emit teamIDChanged();
}
