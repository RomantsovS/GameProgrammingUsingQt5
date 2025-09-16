#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "carinfoproxy.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    QString msg = QStringLiteral("Objects of type CarInfoEngine cannot be created");
    qmlRegisterUncreatableType<CarInfoEngine>("CarInfo", 1, 0, "CarInfoEngine", msg);

    qmlRegisterType<CarInfoProxy>("CarInfo", 1, 0, "CarInfo");

    engine.loadFromModule("dashboard", "Main"); // engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
