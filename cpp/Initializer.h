#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <QObject>
#include <QSharedMemory>

#include "cpp/support/Log.h"

#define UNIQUE_KEY_PREVENT_DOUBLE_RUN "PetanqueTeam-IsRunning-mt9n8MSxmKiEUZo"

class Initializer : public QObject
{
    Q_OBJECT

private:
    explicit Initializer(QObject *parent = nullptr);
    Initializer(const Initializer &) = delete; // rm copy constructor
    Initializer(      Initializer &&) = delete; // rm move constructor
    Initializer& operator=(const Initializer &) = delete; // rm copy operator
    Initializer& operator=(      Initializer &&) = delete; // rm move operator (y = std::move(x))

public slots:
    static Initializer *const getInstance() noexcept;

    void initialize() noexcept; /// start point

private:
    static bool testIfApplicationAlreadyRunning() noexcept; /// step, that if fail, cannot be retry

signals:
    void initialized(); /// positive end

    void applicationIsAlreadyRunning(); /// negative end
};

#endif // INITIALIZER_H
