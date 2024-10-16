#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QFile>

#include "cpp/support/Log.h"

#define BOOL_TO_STR(x) ( (x) ? QString("true") : QString("false") )

#define MAIN_DB_CONNECTION "MainDatabaseConnection"
#define DATABASE_FILE "Petanque.db"
#define DELETE_DB_AT_START true
#define ADD_EXAMPLE_DATA_TO_TABLE true

class Database : public QObject
{
    Q_OBJECT

private:
    explicit Database(QObject *parent = nullptr);
    Database(const Database &) = delete; // rm copy constructor
    Database(      Database &&) = delete; // rm move constructor
    Database& operator=(const Database &) = delete; // rm copy operator
    Database& operator=(      Database &&) = delete; // rm move operator (y = std::move(x))
    ~Database();

public:
    static Database * const getInstance() noexcept;

    void initialize();

    const QString &getLastError() const;

private:
    bool openDB();
    void closeDB();
    bool resetDB();
    bool createTableEvents();
    bool tableEventsExist() const;
    void createExampleEventsData() const;

private slots:

signals:
    void initialized();
    void initializeFailed();

    void contentOfDatabaseChanged();

private:
    bool m_oppened;
    QString m_lastError;
};

#endif // DATABASE_H
