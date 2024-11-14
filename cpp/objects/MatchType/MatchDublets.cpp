#include "MatchDublets.h"

MatchDublets::MatchDublets(uint playersCount, QObject *parent)
    : MatchTypeBase{playersCount, 3, parent}
{}

bool MatchDublets::isSelectionDataValid(QString *message) const
{
    return MatchTypeBase::isSelectionDataValid(2, 3, message);
}
