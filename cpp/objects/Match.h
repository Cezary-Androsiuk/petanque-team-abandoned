#ifndef MATCH_H
#define MATCH_H

#include <QObject>

class Match : public QObject
{
    Q_OBJECT
public:
    explicit Match(QObject *parent = nullptr);

signals:
};

#endif // MATCH_H
