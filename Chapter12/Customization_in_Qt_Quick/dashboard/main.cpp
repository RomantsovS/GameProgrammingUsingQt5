#include <QApplication>
#include <QQmlApplicationEngine>

#include "carinfo.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("dashboard", "Main");

    CarInfo cinfo;
    cinfo.show();

    return app.exec();
}
