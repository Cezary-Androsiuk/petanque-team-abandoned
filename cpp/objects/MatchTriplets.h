#ifndef MATCHTRIPLETS_H
#define MATCHTRIPLETS_H

#include <QObject>
#include <QVector>

#include "cpp/support/Log.h"

class MatchTriplets : public QObject
{
    Q_OBJECT
public:
    explicit MatchTriplets(int playersCount, QObject *parent = nullptr);

signals:

private:
    QVector<QVector<bool>> m_selection; // rows<columns> [row][col]
};

#endif // MATCHTRIPLETS_H
