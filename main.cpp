#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QUrl>

#include "cpp/Initializer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

// /// tell QML if application is in debug mode
// #ifdef QT_DEBUG
//     engine.rootContext()->setContextProperty("isDebugMode", true);
// #else
//     engine.rootContext()->setContextProperty("isDebugMode", false);
// #endif

    engine.rootContext()->setContextProperty("Initializer", Initializer::getInstance());

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
