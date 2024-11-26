#include "Selection.h"

Selection::Selection(uint rows, uint columns, QObject *parent)
    : QObject{parent}
    , m_rows{rows}
    , m_columns{columns}
    , m_values(rows, QVector<bool>(columns, false))
{}

bool Selection::isDataValid(const int rangeOfPlayersCountInGroup[], QString *message) const
{
    QVector<int> selectionCountsInGroups(m_columns, 0);
    this->countSelectionsInGroups(selectionCountsInGroups);

    /// range is [min, max] (including)
    const int minPlayersInGroup = rangeOfPlayersCountInGroup[0];
    const int maxPlayersInGroup = rangeOfPlayersCountInGroup[1];

    for(int i=0; i<m_columns; i++)
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
    if(groups.size() != m_columns)
    {
        W("cannot count selections in groups due to uneven groups count")
        return;
    }

    for(int ri=0; ri<m_rows; ri++)
    {
        const QVector<bool> &row = m_values[ri];

        for(int ci=0; ci<m_columns; ci++)
        {
            if(row[ci])
                groups[ci]++;
        }
    }
}

void Selection::setValueForCell(uint row, uint column, bool value)
{
    /// input value protection (always use protection)
    if(m_values.size() <= row)
    {
        W(QAPF("trying to access %u row, while this matrix contains %lld rows", row, m_values.size()))
        return;
    }

    if(m_values[row].size() <= column)
    {
        W(QAPF(
            "trying to access %u column in %u row, while this row of matrix contains %lld columns",
            column, row, m_values[row].size() ));
        return;
    }

    /// Binding loop protection
    if(m_values[row][column] == value)
        return;

    /// keep row exclusive
    if(value == true)
    {
        /// set all values in that row to false
        for(int i=0; i<m_values[row].size(); i++)
            m_values[row][i] = false;
    }

    m_values[row][column] = value;

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

uint Selection::getRows() const
{
    return m_rows;
}

uint Selection::getColumns() const
{
    return m_columns;
}
