#include "MatchSingiels.h"

MatchSingiels::MatchSingiels(QObject *parent)
    : QObject{parent}
    , m_playerID{0}
{ }

uint MatchSingiels::getPlayerID() const
{
    return m_playerID;
}

void MatchSingiels::setPlayerID(uint playerID)
{
    if(m_playerID != 0)
        W("adding a new player overwrites the previous m_playerID");

    m_playerID = playerID;
    emit this->playerIDChanged();

}
