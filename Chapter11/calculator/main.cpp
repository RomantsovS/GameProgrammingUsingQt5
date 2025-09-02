#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "advancedcalculator.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
    engine.load(url);
    engine.globalObject().setProperty("advancedCalculator",
                                      engine.newQObject(new AdvancedCalculator));

    // {
    //     QQmlComponent component(&engine);
    //     component.setData(
    //         "import QtQuick 2.6\n"
    //         "import QtQuick.Controls 2.2\n"
    //         "import QtQuick.Window 2.2\n"
    //         "Window { Button { text: \"C++ button\" } }", QUrl());
    //     QObject* object = component.create();
    //     object->setProperty("visible", true);
    //     QMetaObject::invokeMethod(object, "showMaximized");

    // }

    // if (engine.rootObjects().count() == 1) {
    //     QObject *window = engine.rootObjects()[0];
    //     QObject *resetButton = window->findChild<QObject*>("buttonReset");
    //     if (resetButton) {
    //         resetButton->setProperty("highlighted", true);
    //     }

    //     QQmlComponent component(&engine);
    //     component.setData(
    //         "import QtQuick 2.6\n"
    //         "import QtQuick.Controls 2.2\n"
    //         "Button { text: \"C++ button2\" }", QUrl());
    //     QObject *object = component.create();
    //     QObject *calculator = window->findChild<QObject*>("calculator");
    //     object->setProperty("parent", QVariant::fromValue(calculator));

    // }

    return app.exec();
}
