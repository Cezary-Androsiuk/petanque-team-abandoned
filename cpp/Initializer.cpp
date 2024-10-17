#include "cpp/Initializer.h"

Initializer::Initializer(QObject *parent)
    : QObject{parent}
{

}

Initializer *const Initializer::getInstance() noexcept
{
    static Initializer i;
    return &i;
}

void Initializer::initialize() noexcept
{
    /// test shared memory
    if(!Initializer::testIfApplicationAlreadyRunning())
    {
        /// application won't continue if so, just inform user about it
        W("Application is already running");
        emit this->applicationIsAlreadyRunning();
        return;
    }

    emit this->initialized();
}

bool Initializer::testIfApplicationAlreadyRunning() noexcept
{
    D("testing IfApplicationAlreadyRunning")
    static QSharedMemory sharedMemory;
    sharedMemory.setKey(UNIQUE_KEY_PREVENT_DOUBLE_RUN);

    return sharedMemory.create(1);
}


