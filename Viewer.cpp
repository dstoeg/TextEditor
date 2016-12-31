#include "Viewer.h"
#include "Logger.h"
#include "Parser.h"
#include "Helpers.h"
#include <iostream>
#include <sstream>
#include <QVariant>
#include <QDebug>
#include <QFontMetrics>
#include <QQmlProperty>

Viewer::Viewer(PieceListText * text, QObject * canvas) : QObject(0)
{
    mText = text;
    mText->addListener(this);
    mCanvas = canvas;
    mCaretVisible = false;
    mFirstLine = nullptr;
    mFirstTpos = 0;
    mLastTpos = 0;
    mSel = nullptr;
    mLastPos = nullptr;
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
    // TODO adapt to different font sizes
    QFontMetrics m(mCurrentFont);

    Line * first = nullptr;
    Line * line = nullptr;
    size_t y = top;
    mLastTpos = pos;
    char ch = mText->charAt(pos);

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

        std::stringstream buf;
        while (ch != '\n' && ch != EOF) {
            buf << ch;
            pos++;
            ch = mText->charAt(pos);
        }

        bool eol = (ch == '\n');
        if (eol)
        {
            buf << ch;
            pos++;
            ch = mText->charAt(pos);
        }

        std::string str = buf.str();
        line->len = str.size();
        line->text = str;
        line->x = LEFT;
        line->y = y;
        line->w = stringWidth(m, line->text);
        line->h = m.height();
        line->base = y + m.ascent();
        y += line->h;
        mLastTpos += line->len;
        if (!eol) break;
    }
    return first;
}


void Viewer::paint()
{

    Piece * piece = mText->getFirst();
    size_t posY = 20;

    while (piece != nullptr)
    {
        drawString(piece->getText(), 20, posY, piece->getFont());
        posY += 30;
        piece = piece->getNext();
    }
    /*

    if (mFirstLine == nullptr) {
        mFirstLine = fill(TOP, getHeight() - BOTTOM, 0);
        mCaret = Pos(0);
    }
    Line * line = mFirstLine;
    while (line != nullptr) {
        drawString(line->text, line->x, line->base, mCurrentFont);
        line = line->next;
    }
    if (mCaretVisible)
        invertCaret();

    if (mSel != nullptr)
        invertSelection(mSel->beg, mSel->end);
        */
}

void Viewer::drawString(std::string const& s, size_t x, size_t y, QFont const& font)
{
    QString qs(Helpers::ReplaceTabs(s).c_str());
    QString qfont(Parser::getFontAsString(font).c_str());

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
    mCurrentFont.setFamily(font);
}

void Viewer::OnFontSizeChanged(int size)
{
    mCurrentFont.setPixelSize(size);
}

void Viewer::OnFontStyleChanged(bool bold, bool italic, bool underlined)
{
    mCurrentFont.setBold(bold);
    mCurrentFont.setItalic(italic);
    mCurrentFont.setUnderline(underlined);
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

size_t Viewer::stringWidth(QFontMetrics m, std::string const& s)
{
    std::string s1 = Helpers::ReplaceTabs(s);
    return m.width(QString::fromStdString(s1));
}

size_t Viewer::charWidth(QFontMetrics m, char ch)
{
    if (ch == '\t')
        return 4 * m.width(' ');
    else
        return m.width(ch);
}

void Viewer::rebuildFrom(Position pos)
{
    Line * line = pos.line;
    Line * prev = line->prev;
    line = fill(line->y, getHeight() - BOTTOM, pos.org);
    if (prev == nullptr)
        mFirstLine = line;
    else {
        prev->next = line;
        line->prev = prev;
    }
    repaint(LEFT, line->y, getWidth(), getHeight());
}

size_t Viewer::getHeight()
{
    return QQmlProperty::read(mCanvas, "height").toInt();
}

size_t Viewer::getWidth()
{
    return QQmlProperty::read(mCanvas, "width").toInt();
}

void Viewer::repaint(size_t x, size_t y, size_t width, size_t height)
{
    // TODO
}

Position Viewer::Pos(size_t tpos)
{
    return Position();
}

void Viewer::invertSelection(Position beg, Position end)
{

}

void Viewer::setSelection(size_t from, size_t to)
{

}

void Viewer::removeSelection()
{

}

