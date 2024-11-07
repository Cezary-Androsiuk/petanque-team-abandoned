#include "MatchTeam.h"

MatchTeam::MatchTeam(QObject *parent)
    : QObject{parent}
{
    m_triplets.reserve(2);
    m_dublets.reserve(3);
    m_singiels.reserve(6);
}

void MatchTeam::addTriplet(uint playerID[4])
{
    MatchTriplets *mt = new MatchTriplets(this);
    mt->addPlayerID(playerID[0]);
    mt->addPlayerID(playerID[1]);
    mt->addPlayerID(playerID[2]);
    if(playerID[4] != 0)
        mt->addPlayerID(playerID[4]);
    m_triplets.append(mt);
    emit this->tripletsChanged();
}

void MatchTeam::addDublet(uint playerID[3])
{
    MatchDublets *md = new MatchDublets(this);
    md->addPlayerID(playerID[0]);
    md->addPlayerID(playerID[1]);
    if(playerID[3] != 0)
        md->addPlayerID(playerID[3]);
    m_dublets.append(md);
    emit this->dubletsChanged();
}

void MatchTeam::addSingiel(uint playerID)
{
    MatchSingiels *ms = new MatchSingiels(this);
    ms->setPlayerID(playerID);
    m_singiels.append(ms);
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
