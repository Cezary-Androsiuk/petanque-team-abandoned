#ifndef MEMORY_H
#define MEMORY_H

#include <QObject>
#include <QStringList>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "cpp/support/Log.h"

#define MEMORY_DIR "./memory"
#define MEMORY_FILE "./memory/PetanqueMemory.json"
#define DELETE_MEMORY_AT_START true
#define PRINT_VALUES false // if true, prints values after loadPersonalization and before savePersonalization

#define BOOL_TO_STR(x) ( (x) ? QString("true") : QString("false") )

class Memory : public QObject
{
    Q_OBJECT
public:
    explicit Memory(QObject *parent = nullptr);

public slots:
    void load();
    void save();

public:
    Q_INVOKABLE bool memoryFileExist() const;

signals:
    void memorySaved();
    void memoryLoaded();
    void memoryError(QString message);
};

#endif // MEMORY_H
