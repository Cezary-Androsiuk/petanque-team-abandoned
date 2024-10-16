#ifndef PERSONALIZATION_H
#define PERSONALIZATION_H

#include <QObject>
#include <QString>
#include <QStringList>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "cpp/support/Log.h"

#define JSON_FILE "Personalization.json"
#define PRINT_VALUES false // if true, prints values after loadPersonalization and before savePersonalization
#define KEY_NOT_FOUND_MESSAGE W(JSON_FILE " file not contains value related with key: " + key); // requires key variable
#define MARK_ERROR(x) {auto error = (x); W(error); this->addError(error);}

#define BOOL_TO_STR(x) ( (x) ? QString("true") : QString("false") )

/// DEFAULT VALUES
#define DEFAULT_NOTE "### Any change to the contents of this file, may lead to unexpected results ###"
#define DEFAULT_DARK_THEME true

/// KEYS FOR VALUES
#define KEY_NOTE "!NOTE"
#define KEY_DARK_THEME "dark theme"

// Singleton
class Personalization : public QObject
{
    Q_OBJECT
    Q_PROPERTY(const bool &darkTheme READ getDarkTheme NOTIFY darkThemeChanged FINAL)

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
    void save();
    const QString &getErrors() const;

public:
    /// Getters
    const bool &getDarkTheme() const;

    /// Setters
    void setDarkTheme(const bool &darkTheme);

signals:
    void loaded();
    void saved();
    void loadFailed();
    void saveFailed();

    void darkThemeChanged();

private:
    bool m_darkTheme;

    QString m_errors;
};

#endif // PERSONALIZATION_H
