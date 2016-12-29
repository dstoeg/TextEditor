#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQmlContext>


#include "PieceListText.h"
#include "Viewer.h"

using namespace std;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQmlComponent component(&engine, "qrc:/main.qml");

    QObject * root = component.create();
    QObject * canvas = root->findChild<QObject*>("canvas");

    PieceListText text;
    Viewer viewer(&text,canvas);

    engine.rootContext()->setContextProperty("viewer", &viewer);

    return app.exec();
}
