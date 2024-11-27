#include "MatchDublets.h"

MatchDublets::MatchDublets(uint playersCount, QObject *parent)
    : MatchTypeBase{playersCount, 3, parent}
{}

bool MatchDublets::isSelectionDataValid(QString *message) const
{
    const int rangeOfPlayersCountInGroup[2] = {2, 3};
    return _isSelectionDataValid(rangeOfPlayersCountInGroup, message);
}

bool MatchDublets::isMatchPointsDataValid(QString *message) const
{
    return _isMatchPointsDataValid(message);
}
