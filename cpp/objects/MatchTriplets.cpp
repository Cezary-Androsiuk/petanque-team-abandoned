#include "MatchTriplets.h"

MatchTriplets::MatchTriplets(QObject *parent)
    : QObject{parent}
{
    m_playersID.reserve(4);
}

const QList<uint> &MatchTriplets::getPlayersID() const
{
    return m_playersID;
}

void MatchTriplets::addPlayerID(uint playerID)
{
    if(m_playersID.size()>4)
        W("adding a new player exceeds the expected size of m_playersID");

    m_playersID.append(playerID);
    emit this->playersIDChanged();
}
