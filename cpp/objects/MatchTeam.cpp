#include "MatchTeam.h"

MatchTeam::MatchTeam(QObject *parent)
    : QObject{parent}
{
}

uint MatchTeam::getTeamID() const
{
    return m_teamID;
}

const MatchTriplets *MatchTeam::getTriplets() const
{
    return m_triplets;
}

const MatchDublets *MatchTeam::getDublets() const
{
    return m_dublets;
}

const MatchSingiels *MatchTeam::getSingiels() const
{
    return m_singiels;
}

MatchTriplets *MatchTeam::getTripletsRef()
{
    return m_triplets;
}

MatchDublets *MatchTeam::getDubletsRef()
{
    return m_dublets;
}

MatchSingiels *MatchTeam::getSingielsRef()
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


void MatchTeam::setTriplets(MatchTriplets *triplets)
{
    m_triplets = triplets;
}

void MatchTeam::setDublets(MatchDublets *dublets)
{
    m_dublets = dublets;
}

void MatchTeam::setSingiels(MatchSingiels *singiels)
{
    m_singiels = singiels;
}
