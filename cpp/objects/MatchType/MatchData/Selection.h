#ifndef SELECTION_H
#define SELECTION_H

#include <QObject>
#include <QVector>

#include "cpp/support/Log.h"

typedef QVector<QVector<bool>> BoolMatrix;

class Selection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BoolMatrix values READ getValues NOTIFY valuesChanged FINAL)
    Q_PROPERTY(uint rows READ getRows CONSTANT FINAL)
    Q_PROPERTY(uint columns READ getColumns CONSTANT FINAL)

public:
    explicit Selection(uint rows, uint columns, QObject *parent = nullptr);

public:
    bool isDataValid(const int rangeOfPlayersCountInGroup[2], QString *message) const;

private:
    void countSelectionsInGroups(QVector<int> &groups) const;

public slots:
    void setValueForCell(uint row, uint column, bool value);

public:
    const BoolMatrix &getValues() const;
    uint getRows() const;
    uint getColumns() const;

signals:
    void valuesChanged();

private:
    // const uint &m_playersCount; // = m_rows
    // const uint &m_groupsCount; // = m_columns

    const uint m_rows; // players
    const uint m_columns; // groups
    BoolMatrix m_values; // rows<columns> [row][col]
};

#endif // SELECTION_H
