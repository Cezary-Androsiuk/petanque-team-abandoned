#ifndef MATCHPOINTS_H
#define MATCHPOINTS_H

#include <QObject>

typedef QVector<QVector<int>> IntMatrix;

class MatchPoints : public QObject
{
    Q_OBJECT
public:
    explicit MatchPoints(QObject *parent = nullptr);

signals:

private:
    IntMatrix m_points; // rows<coulumns> []
};

#endif // MATCHPOINTS_H
