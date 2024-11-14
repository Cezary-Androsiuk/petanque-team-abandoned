#include "MatchTriplets.h"

MatchTriplets::MatchTriplets(uint playersCount, QObject *parent)
    : QObject{parent}
    , m_rows{playersCount}
    , m_columns{2}
    , m_selection(m_rows, QVector<bool>(m_columns, false))
{}

void MatchTriplets::setSelectionCell(uint row, uint column, bool value)
{
    /// input value protection (always use protection)
    if(m_selection.size() <= row)
    {
        W(QAPF("trying to access %u row, while this matrix contains %lld rows", row, m_selection.size()))
        return;
    }

    if(m_selection[row].size() <= column)
    {
        W(QAPF(
            "trying to access %u column in %u row, while this row of matrix contains %lld columns",
            column, row, m_selection[row].size() ));
        return;
    }

    /// Binding loop protection
    if(m_selection[row][column] == value)
        return;

    /// keep row exclusive
    if(value == true)
    {
        /// set all values in that row to false
        for(int i=0; i<m_selection[row].size(); i++)
            m_selection[row][i] = false;
    }

    m_selection[row][column] = value;

    /// print matrix
    for(const auto &row : m_selection)
    {
        QString rowText;
        for(bool cell : row)
            rowText += QAPF("%c ", cell ? 'x' : ' ');
        qDebug() << rowText.toStdString().c_str();
    }

    emit this->selectionChanged();
}

const BoolMatrix &MatchTriplets::getSelection() const
{
    return m_selection;
}

uint MatchTriplets::getRows() const
{
    return m_rows;
}

uint MatchTriplets::getColumns() const
{
    return m_columns;
}
