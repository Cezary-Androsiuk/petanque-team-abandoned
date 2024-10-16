#include "cpp/Initializer.h"

Initializer::Initializer(QObject *parent)
    : QObject{parent}
{
    m_personalization = Personalization::getInstance();
    m_database = Database::getInstance();
    this->createConnections();
}

void Initializer::createConnections() noexcept
{
    /// init 2
    QObject::connect(m_personalization, &Personalization::loaded, this, &Initializer::personalizationInitialized);
    QObject::connect(m_personalization, &Personalization::loadFailed, this, &Initializer::personalizationInitializeFailed);

    /// init 2 -> init 3
    QObject::connect(this, &Initializer::personalizationInitialized, this, &Initializer::initializeDatabase);

    /// init 3
    QObject::connect(m_database, &Database::initialized, this, &Initializer::databaseInitialized);
    QObject::connect(m_database, &Database::initializeFailed, this, &Initializer::databaseInitializeFailed);

    /// init 3 -> end
    QObject::connect(this, &Initializer::databaseInitialized, this, &Initializer::initialized);
}

Initializer *const Initializer::getInstance() noexcept
{
    static Initializer i;
    return &i;
}

void Initializer::initialize() noexcept
{
    // test shared memory
    if(!Initializer::testIfApplicationAlreadyRunning())
    {
        /// application won't continue if so, just inform user about it
        W("Application is already running");
        emit this->applicationIsAlreadyRunning();
        return;
    }

    this->initializePersonalization();
}

void Initializer::initializePersonalization() noexcept
{
    D("Initializing personalization")
    m_personalization->load();
}

void Initializer::initializeDatabase() noexcept
{
    D("Initializing database")
    m_database->initialize();
}

bool Initializer::testIfApplicationAlreadyRunning() noexcept
{
    QSharedMemory sharedMemory;
    sharedMemory.setKey(UNIQUE_KEY_PREVENT_DOUBLE_RUN);

    return sharedMemory.create(1);
}


