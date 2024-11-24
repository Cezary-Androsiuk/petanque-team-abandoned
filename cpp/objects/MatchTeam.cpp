#include "MatchTeam.h"

MatchTeam::MatchTeam(QObject *parent)
    : QObject{parent}
{
}

MatchTypeBase *MatchTeam::getMatchType(int type) const
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

MatchTypeBase *MatchTeam::getMatchType(int type)
{
    return static_cast<const MatchTeam *>(this)->getMatchType(type);
}

void MatchTeam::setMatchType(MatchTypeBase *matchTypeBase)
{
    if(dynamic_cast<MatchSingiels *>(matchTypeBase))
    {
        m_singiels = static_cast<MatchSingiels *>(matchTypeBase);
    }
    else if(dynamic_cast<MatchDublets *>(matchTypeBase))
    {
        m_dublets = static_cast<MatchDublets *>(matchTypeBase);
    }
    else if(dynamic_cast<MatchTriplets *>(matchTypeBase))
    {
        m_triplets = static_cast<MatchTriplets *>(matchTypeBase);
    }
    else
    {
        W("no matching MatchType for given variable");
    }
}

