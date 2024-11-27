#include "MatchSingiels.h"

MatchSingiels::MatchSingiels(uint playersCount, QObject *parent)
    : MatchTypeBase{playersCount, 6, parent}
{}

bool MatchSingiels::isSelectionDataValid(QString *message) const
{
    const int rangeOfPlayersCountInGroup[2] = {1, 1};
    return _isSelectionDataValid(rangeOfPlayersCountInGroup, message);
}

bool MatchSingiels::isMatchPointsDataValid(QString *message) const
{
    return _isMatchPointsDataValid(message);
}
