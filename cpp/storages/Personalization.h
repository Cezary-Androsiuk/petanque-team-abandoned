#ifndef PERSONALIZATION_H
#define PERSONALIZATION_H

#include <QObject>
#include <QString>
#include <QStringList>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileInfo>

#include "cpp/support/Log.h"

#define JSON_FILE "personalization.json"
#define PRINT_VALUES false // if true, prints values after loadPersonalization and before savePersonalization
#define KEY_NOT_FOUND_MESSAGE W(JSON_FILE " file not contains value related with key: " + key); // requires key variable
#define MARK_ERROR(x) {auto error = (x); W(error); this->addError(error);}

#define BOOL_TO_STR(x) ( (x) ? QString("true") : QString("false") )

/// DEFAULT VALUES
#define DEFAULT_NOTE "### Any change to the contents of this file, may lead to unexpected results ###"

/// KEYS FOR VALUES
#define KEY_NOTE "!NOTE"
#define KEY_EXAMPLE_DATA "example data"

// Singleton
class Personalization : public QObject
{
    Q_OBJECT

private:
    explicit Personalization(QObject *parent = nullptr);
    Personalization(const Personalization &) = delete; // rm copy constructor
    Personalization(      Personalization &&) = delete; // rm move constructor
    Personalization& operator=(const Personalization &) = delete; // rm copy operator
    Personalization& operator=(      Personalization &&) = delete; // rm move operator (y = std::move(x))
    ~Personalization();

private:
    void printValues() const;
    void addError(const QString &error);

public:
    static Personalization *const getInstance() noexcept;

    void setDefault();
    void load();
private:
    void ifNotExistSaveDefault();
    void save();
public:
    const QString &getErrors() const;

public:
    /// Getters
    const QJsonObject &getExampleData() const;

signals:
    void loaded();
    void saved();
    void loadFailed();
    void saveFailed();

private:
    QJsonObject m_exampleData;

    QString m_errors;
};

#endif // PERSONALIZATION_H
