#include "MatchTeam.h"

MatchTeam::MatchTeam(QObject *parent)
    : QObject{parent}
{
}

const MatchSingiels *MatchTeam::getSingiels() const
{
    return m_singiels;
}

const MatchDublets *MatchTeam::getDublets() const
{
    return m_dublets;
}

const MatchTriplets *MatchTeam::getTriplets() const
{
    return m_triplets;
}

MatchSingiels *MatchTeam::getSingielsRef()
{
    return m_singiels;
}

MatchDublets *MatchTeam::getDubletsRef()
{
    return m_dublets;
}

MatchTriplets *MatchTeam::getTripletsRef()
{
    return m_triplets;
}

MatchTypeBase *MatchTeam::getMatchType(const QString &type)
{
    const QString typeLower = type.toLower();
    if(typeLower == "singiels")
    {
        return m_singiels;
    }
    else if(typeLower == "dublets")
    {
        return m_dublets;
    }
    else if(typeLower == "triplets")
    {
        return m_triplets;
    }

    W("no matching MatchType for '" + type + "' type");
    return nullptr;
}

MatchTypeBase *MatchTeam::getMatchType(int type)
{
    if(type == 1)
    {
        return m_singiels;
    }
    else if(type == 2)
    {
        return m_dublets;
    }
    else if(type == 3)
    {
        return m_triplets;
    }

    W("no matching MatchType for '" + QString::number(type) + "' type");
    return nullptr;
}

void MatchTeam::setSingiels(MatchSingiels *singiels)
{
    m_singiels = singiels;
}

void MatchTeam::setDublets(MatchDublets *dublets)
{
    m_dublets = dublets;
}

void MatchTeam::setTriplets(MatchTriplets *triplets)
{
    m_triplets = triplets;
}

