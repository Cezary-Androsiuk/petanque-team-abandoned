#ifndef MATCHSINGIELS_H
#define MATCHSINGIELS_H

#include <QObject>
#include <QVector>

#include "cpp/support/Log.h"

typedef QVector<QVector<bool>> BoolMatrix;

class MatchSingiels : public QObject
{
    Q_OBJECT
public:
    explicit MatchSingiels(int playersCount, QObject *parent = nullptr);

signals:

private:
    QVector<QVector<bool>> m_selection; // rows<columns> [row][col]
};

#endif // MATCHSINGIELS_H
