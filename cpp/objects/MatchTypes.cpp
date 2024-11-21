#include "MatchTypes.h"

MatchTypes::MatchTypes(QObject *parent)
    : QObject{parent}
{
}

uint MatchTypes::getTeamID() const
{
    return m_teamID;
}

const MatchSingiels *MatchTypes::getSingiels() const
{
    return m_singiels;
}

const MatchDublets *MatchTypes::getDublets() const
{
    return m_dublets;
}

const MatchTriplets *MatchTypes::getTriplets() const
{
    return m_triplets;
}

MatchSingiels *MatchTypes::getSingielsRef()
{
    return m_singiels;
}

MatchDublets *MatchTypes::getDubletsRef()
{
    return m_dublets;
}

MatchTriplets *MatchTypes::getTripletsRef()
{
    return m_triplets;
}

void MatchTypes::setTeamID(uint teamID)
{
    if (m_teamID == teamID)
        return;
    m_teamID = teamID;
    emit teamIDChanged();
}

void MatchTypes::setSingiels(MatchSingiels *singiels)
{
    m_singiels = singiels;
}

void MatchTypes::setDublets(MatchDublets *dublets)
{
    m_dublets = dublets;
}

void MatchTypes::setTriplets(MatchTriplets *triplets)
{
    m_triplets = triplets;
}

