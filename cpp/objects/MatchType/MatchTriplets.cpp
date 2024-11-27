#include "MatchTriplets.h"

MatchTriplets::MatchTriplets(uint playersCount, QObject *parent)
    : MatchTypeBase{playersCount, 2, parent}
{}

bool MatchTriplets::isSelectionDataValid(QString *message) const
{
    const int rangeOfPlayersCountInGroup[2] = {3, 4};
    return _isSelectionDataValid(rangeOfPlayersCountInGroup, message);
}

bool MatchTriplets::isMatchPointsDataValid(QString *message) const
{
    return _isMatchPointsDataValid(message);
}
