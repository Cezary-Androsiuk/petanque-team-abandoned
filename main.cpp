#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QUrl>

#include "cpp/Initializer.h"
#include "cpp/Backend.h"
#include "cpp/Login.h"
#include "cpp/Memory.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Backend backend;
    Login login;
    Memory memory;

    engine.rootContext()->setContextProperty("Initializer", Initializer::getInstance());
    engine.rootContext()->setContextProperty("Backend", &backend);
    engine.rootContext()->setContextProperty("Login", &login);
    engine.rootContext()->setContextProperty("Memory", &memory);

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
