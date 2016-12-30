#include "Viewer.h"
#include "Logger.h"
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

bool Viewer::OnLoadFile(QString str)
{
    return mText->load(str.toStdString());
}

Line * Viewer::fill(size_t top, size_t bottom, size_t pos)
{
    //g = getGraphics();
    //FontMetrics m = g.getFontMetrics();
    /*
    Line * first = nullptr;
    Line * line = nullptr;
    size_t y = top;
    mLastTpos = pos;
    char ch = text.charAt(pos);

    while (y < bottom) {
        if (first == nullptr) {
            first = new Line();
            line = first;
        } else {
            Line * prev = line;
            line->next = new Line();
            line = line->next;
            line->prev = prev;
        }
        StringBuffer buf = new StringBuffer();
        while (ch != '\n' && ch != EOF) {
            buf.append(ch);
            pos++;
            ch = text.charAt(pos);
        }
        boolean eol = ch == '\n';
        if (eol) { buf.append(ch); pos++; ch = text.charAt(pos); }
        line.len = buf.length();
        line.text = buf.toString();
        line.x = LEFT;
        line.y = y;
        line.w = stringWidth(m, line.text);
        line.h = m.getHeight();
        line.base = y + m.getAscent();
        y += line.h;
        lastTpos += line.len;
        if (!eol) break;
    }
    return first;*/
    return 0;
}

void Viewer::paint()
{
    drawString("test", 20, 20, "20px sans-serif", 0);

    drawString("anotherTest", 20, 100, "50px monospace", 0);

    /*
    if (firstLine == nullptr) {
        firstLine = fill(TOP, getHeight() - BOTTOM, 0);
        caret = Pos(0);
    }
    Line * line = firstLine;
    while (line != nullptr) {
        drawString(g, line.text, line.x, line.base);
        line = line.next;
    }
    if (caret != null) invertCaret();
    if (sel != null) invertSelection(sel.beg, sel.end);*/
}

void Viewer::drawString(std::string const& s, size_t x, size_t y, std::string const& font, int style)
{
    QString qs(s.c_str());
    QString qfont(font.c_str());

    QMetaObject::invokeMethod(mCanvas, "drawString",
                              Q_ARG(QVariant, qs),
                              Q_ARG(QVariant, x),
                              Q_ARG(QVariant, y),
                              Q_ARG(QVariant, qfont),
                              Q_ARG(QVariant, style));
}
