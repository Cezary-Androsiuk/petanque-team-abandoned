#ifndef SELECTION_H
#define SELECTION_H

#include <QObject>

class Selection : public QObject
{
    Q_OBJECT
public:
    explicit Selection(QObject *parent = nullptr);

signals:
};

#endif // SELECTION_H
