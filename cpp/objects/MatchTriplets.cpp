#include "MatchTriplets.h"

MatchTriplets::MatchTriplets(int playersCount, QObject *parent)
    : QObject{parent}
    , m_selection(playersCount, QVector<bool>(2, false))
{}
