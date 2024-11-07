#include "MatchDublets.h"

MatchDublets::MatchDublets(QObject *parent)
    : QObject{parent}
{
    m_playersID.reserve(3);
}

const QList<uint> &MatchDublets::getPlayersID() const
{
    return m_playersID;
}

void MatchDublets::addPlayerID(uint playerID)
{
    if(m_playersID.size()>4)
        W("adding a new player exceeds the expected size of m_playersID");

    m_playersID.append(playerID);
    emit this->playersIDChanged();

}
