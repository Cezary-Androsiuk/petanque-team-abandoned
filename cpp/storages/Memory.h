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
#include "cpp/Backend.h"
#include "cpp/objects/Event.h"

#define MEMORY_DIR "./memory"
#define MEMORY_FILE "./memory/PetanqueMemory.json"
#define DELETE_MEMORY_AT_START false
#define PRINT_VALUES false // if true, prints values after loadPersonalization and before savePersonalization

#define BOOL_TO_STR(x) ( (x) ? QString("true") : QString("false") )

class Memory : public QObject
{
    Q_OBJECT
public:
    explicit Memory(QObject *parent = nullptr);

public slots:
    void load();
    void save(bool reloadAfterSaved = false);

public:
    void setBackendPtr(Backend *backend);

private:
    void jsonToEvent(const QJsonObject &jsonObject, Event *const event) const;
    void jsonToTeams(const QJsonArray &jTeams, Event *const event) const;
    void jsonToMatches(const QJsonArray &jMatches, Event *const event) const;

    void eventToJson(const Event *const event, QJsonObject &jsonObject) const;
    void teamsToJson(const Event *const event, QJsonArray &jTeams) const;
    void matchesToJson(const Event *const event, QJsonArray &jMatches) const;

signals:
    void memoryFileNotExist();
    void memorySaved(bool reload);
    void memorySaveError(QString message);
    void memoryLoaded();
    void memoryLoadError(QString message);

private:
    Backend *m_backend;
};

#endif // MEMORY_H
