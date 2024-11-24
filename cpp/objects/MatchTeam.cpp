#include "MatchTeam.h"

MatchTeam::MatchTeam(QObject *parent)
    : QObject{parent}
{
}

MatchTypeBase *MatchTeam::getMatchType(int type) const
{
    MatchTypeBase *mtb = this->_getMatchType(type);
    if(!mtb)
        W("need to return nullptr pointer - mark the track of the program")
    return mtb;
}

MatchTypeBase *MatchTeam::getMatchType(int type)
{
    MatchTypeBase *mtb = this->_getMatchType(type);
    if(!mtb)
        W("need to return nullptr pointer - mark the track of the program")
    return mtb;
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

MatchTypeBase *MatchTeam::_getMatchType(int type) const
{
    switch(type)
    {
    case 1: return m_singiels;
    case 2: return m_dublets;
    case 3: return m_triplets;
    default:
        W("no matching MatchType for '" + QString::number(type) + "' type");
        return nullptr;
    }
}

