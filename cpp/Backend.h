#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QList>
#include <QVariant>

#include "cpp/support/Log.h"
#include "cpp/objects/Event.h"
#include "cpp/storages/Personalization.h"

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Event* event READ getEvent CONSTANT FINAL)

public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();
    Event *getEvent() const;

    Q_INVOKABLE void createExampleData();

public slots:
    void validateData();
    bool debugMemoryFileExist();
    void debugDeleteMemory();

    // QString isSelectionDataValid(QVariantList data, int groupSize, int groupsCount);

private:


signals:
    void dataValidatedCorrectly();
    void dataValidationFailed(QString description);

private:
    Event *m_event;

};

#endif // BACKEND_H
