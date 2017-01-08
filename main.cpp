#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQmlContext>
#include "Viewer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQmlComponent component(&engine, "qrc:/main.qml");

    QObject * root = component.create();
    QObject * canvas = root->findChild<QObject*>("canvas");

    Viewer viewer(canvas);
    engine.rootContext()->setContextProperty("viewer", &viewer);

    return app.exec();
}
