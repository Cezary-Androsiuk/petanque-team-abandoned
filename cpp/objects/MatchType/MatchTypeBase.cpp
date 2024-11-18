#include "MatchTypeBase.h"

MatchTypeBase::MatchTypeBase(uint playersCount, uint groups, QObject *parent)
    : QObject{parent}
    , m_rows{playersCount}
    , m_columns{groups}
    , m_selection(playersCount, QVector<bool>(m_columns, false))
    , m_usedPlayersInGroups(groups, PlayerList())
{}

bool MatchTypeBase::isSelectionDataValid(const int minSelections, const int maxSelections, QString *message) const
{
    QVector<int> selectionCountsInGroups(m_columns, 0);
    this->countSelectionsInGroups(selectionCountsInGroups);

    for(int i=0; i<m_columns; i++)
    {
        int selectionsCountInGroup = selectionCountsInGroups[i];
        if(minSelections <= selectionsCountInGroup && selectionsCountInGroup <= maxSelections)
            continue;

        QString _message = QAPF_T(
            "in group %d, %d players were selected, but %d or %d were expected",
            i+1, selectionsCountInGroup, minSelections, maxSelections);
        I(_message);

        if(message != nullptr)
            *message = _message;
        return false;
    }

    return true;
}

void MatchTypeBase::countSelectionsInGroups(QVector<int> &groups) const
{
    if(groups.size() != m_columns)
    {
        W("cannot count selections in groups due to uneven groups count")
        return;
    }

    for(int ri=0; ri<m_rows; ri++)
    {
        const QVector<bool> &row = m_selection[ri];

        for(int ci=0; ci<m_columns; ci++)
        {
            if(row[ci])
                groups[ci]++;
        }
    }
}

void MatchTypeBase::setSelectionCell(uint row, uint column, bool value)
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
    // for(const auto &row : m_selection)
    // {
    //     QString rowText;
    //     for(bool cell : row)
    //         rowText += QAPF("%c ", cell ? 'x' : ' ');
    //     qDebug() << rowText.toStdString().c_str();
    // }

    emit this->selectionChanged();
}

void MatchTypeBase::computePlayersUsed(const PlayerList &players)
{
    if(!isSelectionDataValid())
    {
        I("Skipping computing used players, due to invalid data");
        return;
    }

    if(players.size() != m_rows)
    {
        W("players size(" + QString::number(players.size()) + ") is not equal to count of rows(" + QString::number(m_rows) + ")");
        return;
    }

    /// clear usedPlayersInGroups
    for(int i=0; i<m_columns; i++)
    {
        for(Player *p : m_usedPlayersInGroups[i])
            delete p;
        m_usedPlayersInGroups.clear();
    }

    /// create and add player to list coresponding to group
    for(int i=0; i<m_columns; i++)
    {
        for(int j=0; j<m_rows; j++)
        {
            if(!m_selection[j][i])
                continue;

            Player *player = players[j];
            Player *newPlayer = new Player(this);
            newPlayer->copyFromOtherPlayer(*player);
            m_usedPlayersInGroups[i].append(newPlayer);
        }
    }
}

const BoolMatrix &MatchTypeBase::getSelection() const
{
    return m_selection;
}

uint MatchTypeBase::getRows() const
{
    return m_rows;
}

uint MatchTypeBase::getColumns() const
{
    return m_columns;
}
