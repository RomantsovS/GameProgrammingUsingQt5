#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "carinfo.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CarInfo cinfo;
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    engine.loadFromModule("dashboard", "Main");

    engine.rootContext()->setContextProperty("carData", &cinfo);
    // engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    cinfo.show();

    return app.exec();
}
