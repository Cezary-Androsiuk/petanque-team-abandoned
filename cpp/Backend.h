#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

#include "cpp/support/Log.h"

class Backend : public QObject
{
    Q_OBJECT

public:
    explicit Backend(QObject *parent = nullptr);

signals:

private:
};

#endif // BACKEND_H
