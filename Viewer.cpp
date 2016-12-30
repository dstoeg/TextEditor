#include "Viewer.h"
#include "Logger.h"
#include "Parser.h"
#include <iostream>
#include <QVariant>
#include <QDebug>
#include <QFontMetrics>

Viewer::Viewer(PieceListText * text, QObject * canvas) : QObject(0)
{
    mText = text;
    mText->addListener(this);
    mCanvas = canvas;
    mCaretVisible = false;
    mFirstLine = nullptr;
    mFirstTpos = 0;
    mLastTpos = 0;
    //Selection * mSel;
    //Position * mLastPos;
}

void Viewer::update(UpdateEvent e)
{
    // TODO
    QMetaObject::invokeMethod(mCanvas, "requestPaint");
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
    setCaret(x, y);

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

    Piece * piece = mText->getFirst();
    size_t posY = 20;

    while (piece != nullptr)
    {
        std::string fontStr = Parser::getFontAsString(piece->getFont());
        drawString(piece->getText(), 20, posY, fontStr);
        posY += 30;
        piece = piece->getNext();
    }

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

void Viewer::drawString(std::string const& s, size_t x, size_t y, std::string const& font)
{
    QString qs(s.c_str());
    QString qfont(font.c_str());

    QMetaObject::invokeMethod(mCanvas, "drawString",
                              Q_ARG(QVariant, qs),
                              Q_ARG(QVariant, x),
                              Q_ARG(QVariant, y),
                              Q_ARG(QVariant, qfont));
}


bool Viewer::OnSaveFile(QString file)
{
    return mText->save();
}

void Viewer::OnCut()
{
    qDebug() << "cut";
}

void Viewer::OnCopy()
{
    qDebug() << "copy";
}

void Viewer::OnPaste()
{
    qDebug() << "paste";
}

void Viewer::OnFind(QString str)
{
    qDebug() << "find: " << str;
}

void Viewer::OnFontChanged(QString font)
{
    qDebug() << font;

}

void Viewer::OnFontSizeChanged(int size)
{
    qDebug() << size;
}

void Viewer::OnFontStyleChanged(bool bold, bool italic, bool underlined)
{
    qDebug() << "bold " << bold;
    qDebug() << "italic " << italic;
    qDebug() << "underlined " << underlined;
}



void Viewer::invertCaret() {
    QMetaObject::invokeMethod(mCanvas, "invertCaret",
                              Q_ARG(QVariant, mCaret.x),
                              Q_ARG(QVariant, mCaret.y));
    update(UpdateEvent(0,0,""));
}

void Viewer::setCaret(Position pos) {
    removeCaret();
    // removeSelection(); TODO
    mCaret = pos;
    mCaretVisible = true;
    invertCaret();
}

void Viewer::setCaret(size_t tpos) {
    // TODO
}

void Viewer::setCaret(size_t x, size_t y) {
    setCaret(Pos(x, y));
}

void Viewer::removeCaret() {
    if (mCaretVisible)
        invertCaret();
    mCaretVisible = false;
}

Position Viewer::Pos(size_t x, size_t y)
{
    // TODO
    Position pos;
    pos.x = x;
    pos.y = y;
    return pos;
}
