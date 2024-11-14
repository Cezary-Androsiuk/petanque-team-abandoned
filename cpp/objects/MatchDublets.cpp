#include "MatchDublets.h"

MatchDublets::MatchDublets(int playersCount, QObject *parent)
    : QObject{parent}
    , m_selection(playersCount, QVector<bool>(3, false))
{}
