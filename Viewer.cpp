#include "Viewer.h"
#include <iostream>
#include <QVariant>
#include <QDebug>

Viewer::Viewer(PieceListText * text, QObject * canvas) : QObject(0)
{
    mText = text;
    mText->addListener(this);
    mCanvas = canvas;
}

void Viewer::update(UpdateEvent e)
{

}

QString Viewer::testToGui()
{
    return QString("this is coming from model");
}

void Viewer::testFromGui()
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(mCanvas, "test", Q_RETURN_ARG(QVariant, returnedValue));
    std::cout << returnedValue.toString().toStdString();
}

void Viewer::OnKeyPressed(int key)
{
    if (key == Qt::Key_Up)
        std::cout << "up pressed";
    else if (key == Qt::Key_Down)
        std::cout << "down pressed";
    else if (key == Qt::Key_Left)
        std::cout << "left pressed";
    else if (key == Qt::Key_Right)
        std::cout << "right pressed";

    return;
}

void Viewer::OnKeyTyped(int key)
{
    if (key == Qt::Key_Backspace)
        std::cout << "backspace pressed";
    else if (key == Qt::Key_Escape)
        std::cout << "backspace pressed";
    else if (key == Qt::Key_Enter)
        std::cout << "enter pressed";
    else
        std::cout << char(key) << " pressed";

}

void Viewer::OnMouseClicked(int x, int y)
{
    qDebug() << "clicked";
}

void Viewer::OnMouseDragged(int x, int y)
{
    qDebug() << "dragged";
}

void Viewer::OnMouseReleased()
{
    qDebug() << "released";
}
