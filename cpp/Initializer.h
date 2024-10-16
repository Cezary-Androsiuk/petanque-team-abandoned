#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <QObject>
#include <QSharedMemory>

#include "cpp/storages/Personalization.h"
#include "cpp/storages/Database.h"

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

    void createConnections() noexcept;

public slots:
    static Initializer *const getInstance() noexcept;

    /// init 0
    void initialize() noexcept; /// start point

private:
    /// init 1
    static bool testIfApplicationAlreadyRunning() noexcept; /// step, that if fail, cannot be reused

public slots:
    /// init 2
    void initializePersonalization() noexcept; /// step that can be reused (due to user decision)

    /// init 3
    void initializeDatabase() noexcept; /// step that can be reused (due to user decision)

signals:
    /// init 0
    void initialized(); /// positive end

    /// init 1
    void applicationIsAlreadyRunning(); /// negative end

    /// init 2
    void personalizationInitialized();      /// positive step
    void personalizationInitializeFailed(); /// negative step - requires decision from user

    /// init 3
    void databaseInitialized();         /// positive step
    void databaseInitializeFailed();    /// negative step - requires decision from user

private:
    Personalization *m_personalization;
    Database *m_database;
};

#endif // INITIALIZER_H
