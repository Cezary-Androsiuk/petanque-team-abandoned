#ifndef MATCHSELECTION_H
#define MATCHSELECTION_H

#include <QObject>

class MatchSelection : public QObject
{
    Q_OBJECT
public:
    explicit MatchSelection(QObject *parent = nullptr);

signals:
};

#endif // MATCHSELECTION_H
