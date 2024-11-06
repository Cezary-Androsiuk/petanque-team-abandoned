#include "MatchTeam.h"

MatchTeam::MatchTeam(QObject *parent)
    : QObject{parent}
{}

void MatchTeam::addTriplet(uint playerID[4])
{

    emit this->tripletsChanged();
}

void MatchTeam::addDublet(uint playerID[3])
{

    emit this->dubletsChanged();
}

void MatchTeam::addSingiel(uint playerID)
{

    emit this->singielsChanged();
}

uint MatchTeam::getTeamID() const
{
    return m_teamID;
}

const QList<MatchTriplets *> &MatchTeam::getTriplets() const
{
    return m_triplets;
}

const QList<MatchDublets *> &MatchTeam::getDublets() const
{
    return m_dublets;
}

const QList<MatchSingiels *> &MatchTeam::getSingiels() const
{
    return m_singiels;
}

void MatchTeam::setTeamID(uint teamID)
{
    if (m_teamID == teamID)
        return;
    m_teamID = teamID;
    emit teamIDChanged();
}
