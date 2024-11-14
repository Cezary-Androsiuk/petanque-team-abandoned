#include "MatchSingiels.h"

MatchSingiels::MatchSingiels(uint playersCount, QObject *parent)
    : MatchTypeBase{playersCount, 6, parent}
{}

bool MatchSingiels::isSelectionDataValid(QString *message) const
{
    return MatchTypeBase::isSelectionDataValid(1, 1, message);
}
