#include "MatchSingiels.h"

MatchSingiels::MatchSingiels(int playersCount, QObject *parent)
    : QObject{parent}
    , m_selection(playersCount, QVector<bool>(6, false))
{}
