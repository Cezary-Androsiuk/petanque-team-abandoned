#include "Selection.h"

Selection::Selection(uint playersCount, uint groupsCount, QObject *parent)
    : QObject{parent}
    , m_playersCount{playersCount}
    , m_groupsCount{groupsCount}
    , m_values(playersCount, QVector<bool>(groupsCount, false))
{}

bool Selection::isDataValid(const int rangeOfPlayersCountInGroup[], QString *message) const
{
    QVector<int> selectionCountsInGroups(m_groupsCount, 0);
    this->countSelectionsInGroups(selectionCountsInGroups);

    /// range is [min, max] (including)
    const int minPlayersInGroup = rangeOfPlayersCountInGroup[0];
    const int maxPlayersInGroup = rangeOfPlayersCountInGroup[1];

    for(int i=0; i<m_groupsCount; i++)
    {
        int selectionsCountInGroup = selectionCountsInGroups[i];
        if(minPlayersInGroup <= selectionsCountInGroup && selectionsCountInGroup <= maxPlayersInGroup)
            continue;

        QString _message = QAPF_T(
            "in group %d, %d players were selected, but %d or %d were expected",
            i+1, selectionsCountInGroup, minPlayersInGroup, maxPlayersInGroup);
        I(_message);

        if(message != nullptr)
            *message = _message;
        return false;
    }

    return true;
}

void Selection::countSelectionsInGroups(QVector<int> &groups) const
{
    if(groups.size() != m_groupsCount)
    {
        W("cannot count selections in groups due to uneven groups count")
        return;
    }

    for(int ri=0; ri<m_playersCount; ri++)
    {
        const QVector<bool> &row = m_values[ri];

        for(int ci=0; ci<m_groupsCount; ci++)
        {
            if(row[ci])
                groups[ci]++;
        }
    }
}

void Selection::setValueForCell(uint playerIndex, uint column, bool value)
{
    /// input value protection (always use protection)
    if(m_values.size() <= playerIndex)
    {
        W(QAPF("trying to access %u row/playerIndex, while this matrix contains %lld rows/players", playerIndex, m_values.size()))
        return;
    }

    if(m_values[playerIndex].size() <= column)
    {
        W(QAPF(
            "trying to access %u column in %u row/playerIndex, while this row/playerIndex of matrix contains %lld columns",
            column, playerIndex, m_values[playerIndex].size() ));
        return;
    }

    /// Binding loop protection
    if(m_values[playerIndex][column] == value)
        return;

    /// keep row exclusive
    if(value == true)
    {
        /// set all values in that row to false
        for(int i=0; i<m_values[playerIndex].size(); i++)
            m_values[playerIndex][i] = false;
    }

    m_values[playerIndex][column] = value;

    /// print matrix
    // for(const auto &row : m_values)
    // {
    //     QString rowText;
    //     for(bool cell : row)
    //         rowText += QAPF("%c ", cell ? 'x' : ' ');
    //     qDebug() << rowText.toStdString().c_str();
    // }

    emit this->valuesChanged();
}

const BoolMatrix &Selection::getValues() const
{
    return m_values;
}

uint Selection::getPlayersCount() const
{
    return m_playersCount;
}

uint Selection::getGroupsCount() const
{
    return m_groupsCount;
}
