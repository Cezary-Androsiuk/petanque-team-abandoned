#ifndef MATCHPOINTS_H
#define MATCHPOINTS_H

#include <QObject>

class MatchPoints : public QObject
{
    Q_OBJECT
public:
    explicit MatchPoints(QObject *parent = nullptr);

signals:
};

#endif // MATCHPOINTS_H
