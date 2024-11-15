#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QUrl>

#include "cpp/support/LogQML.h"
#include "cpp/Initializer.h"
#include "cpp/Backend.h"
#include "cpp/Login.h"
#include "cpp/storages/Memory.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    LogQML *logQML = new LogQML(&app);

    Backend *backend = new Backend(&app);
    Login *login = new Login(&app);
    Memory *memory = new Memory(&app);
    memory->setBackendPtr(backend);

    engine.rootContext()->setContextProperty("Initializer", Initializer::getInstance());
    engine.rootContext()->setContextProperty("Backend", backend);
    engine.rootContext()->setContextProperty("Login", login);
    engine.rootContext()->setContextProperty("Memory", memory);
    engine.rootContext()->setContextProperty("log", logQML);

    const QUrl url(QStringLiteral("qrc:/PetanqueTeam/qml/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        Initializer::getInstance(),
        &Initializer::initialize);
    engine.load(url);

    return app.exec();
}
