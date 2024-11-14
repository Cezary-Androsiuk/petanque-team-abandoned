#ifndef MATCHTYPEBASE_H
#define MATCHTYPEBASE_H

#include <QObject>
#include <QVector>

#include "cpp/support/Log.h"

typedef QVector<QVector<bool>> BoolMatrix;

class MatchTypeBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BoolMatrix selection READ getSelection NOTIFY selectionChanged FINAL)
    Q_PROPERTY(uint rows READ getRows CONSTANT FINAL)
    Q_PROPERTY(uint columns READ getColumns CONSTANT FINAL)
public:
    explicit MatchTypeBase(uint playersCount, uint groups, QObject *parent = nullptr);

    virtual bool isSelectionDataValid(QString *message = nullptr) const = 0;

protected:
    bool isSelectionDataValid(const int minSelections, const int maxSelections, QString *message) const;
    void countSelectionsInGroups(QVector<int> &groups) const;

public slots:
    void setSelectionCell(uint row, uint column, bool value);

public:
    const BoolMatrix &getSelection() const;
    uint getRows() const;
    uint getColumns() const;

signals:
    void selectionChanged();

protected:
    const uint m_rows; // players
    const uint m_columns; // groups
    BoolMatrix m_selection; // rows<columns> [row][col]
};

#endif // MATCHTYPEBASE_H
