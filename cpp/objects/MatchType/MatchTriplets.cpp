#include "MatchTriplets.h"

MatchTriplets::MatchTriplets(uint playersCount, QObject *parent)
    : MatchTypeBase{playersCount, 2, parent}
{}

bool MatchTriplets::isSelectionDataValid(QString *message) const
{
    return MatchTypeBase::isSelectionDataValid(3, 4, message);
}
