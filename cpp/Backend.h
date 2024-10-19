#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QList>

#include "cpp/support/Log.h"
#include "cpp/objects/Team.h"

class Backend : public QObject
{
    Q_OBJECT

public:
    explicit Backend(QObject *parent = nullptr);

signals:

private:
    QList<Team*> m_teams;
};

#endif // BACKEND_H
