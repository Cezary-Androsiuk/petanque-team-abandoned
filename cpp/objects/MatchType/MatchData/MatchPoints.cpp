#include "MatchPoints.h"

MatchPoints::MatchPoints(uint rows, QObject *parent)
    : QObject{parent}
    , m_rows{rows}
    , m_points(rows, 0)
{}

bool MatchPoints::isDataValid(QString *message) const
{
    return true;
}

void MatchPoints::setPointsForPlayer(uint playerIndex, int value)
{
    if(playerIndex >= m_points.size())
    {
        QString pi = QString::number(playerIndex);
        QString ps = QString::number(m_points.size());
        W("given player index("+ pi +") is larger than size of vector(" +ps+ ")");
        return;
    }

    if(m_points[playerIndex] == value)
        return;

    m_points[playerIndex] = value;
    emit this->pointsChanged();
}

const IntVector &MatchPoints::getPoints() const
{
    return m_points;
}

uint MatchPoints::getRows() const
{
    return m_rows;
}
