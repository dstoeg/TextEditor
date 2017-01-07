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
    mCaret.valid = false;
    mFirstLine = nullptr;
    mFirstTpos = 0;
    mLastTpos = 0;
    mLastPos.valid = false;

    // default font Calibri 20px
    mCurrentFont.setFamily("Calibri");
    mCurrentFont.setPixelSize(30);
    mCurrentFont.setBold(false);
    mCurrentFont.setItalic(false);
    mCurrentFont.setUnderline(false);
}

//--------------------------------------------------------------------------
// GUI event handlers
//--------------------------------------------------------------------------

bool Viewer::OnLoadFile(QString str)
{
    return mText->load(str.toStdString());
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

//--------------------------------------------------------------------------
// delegates to canvas
//--------------------------------------------------------------------------

int Viewer::getHeight()
{
    return QQmlProperty::read(mCanvas, "height").toInt();
}

int Viewer::getWidth()
{
    return QQmlProperty::read(mCanvas, "width").toInt();
}

void Viewer::repaint(int x, int y, int width, int height)
{
    QMetaObject::invokeMethod(mCanvas, "repaint",
                              Q_ARG(QVariant, x),
                              Q_ARG(QVariant, y),
                              Q_ARG(QVariant, width),
                              Q_ARG(QVariant, height));
}

void Viewer::invertSelectionOnCanvas(int x, int y, int width, int height)
{
    QMetaObject::invokeMethod(mCanvas, "invertSelection",
                              Q_ARG(QVariant, x),
                              Q_ARG(QVariant, y),
                              Q_ARG(QVariant, width),
                              Q_ARG(QVariant, height));
}

//--------------------------------------------------------------------------
// position handling
//--------------------------------------------------------------------------

Position Viewer::Pos(int x, int y)
{
    Position pos;
    if (y >= getHeight() - BOTTOM)
        y = getHeight() - BOTTOM - 1;

    Line * line = mFirstLine;
    Line * last = nullptr;
    pos.org = mFirstTpos;

    while (line != nullptr && y >= line->y + line->h) {
        pos.org += line->len;
        last = line;
        line = line->next;
    }

    if (line == nullptr) {
        line = last;
        pos.org -= last->len;
    }

    pos.y = line->base;
    pos.line = line;

    if (x >= line->x + line->w) {
        pos.x = line->x + line->w;
        pos.off = line->len;
        if (pos.org + line->len < mText->getLength())
            pos.off -= 1; // CHECK ??? 2
    }
    else {
        pos.x = line->x;
        QFontMetrics m(mCurrentFont);
        int i = pos.org;
        char ch = mText->charAt(i);
        int w = charWidth(m, ch);
        while (x >= pos.x + w) {
            pos.x += w;
            i++;
            ch = mText->charAt(i);
            w = charWidth(m, ch);
        }
        pos.off = i - pos.org;
    }
    pos.tpos = pos.org + pos.off;
    return pos;
}

Position Viewer::Pos(int tpos)
{
    if (tpos < mFirstTpos)
        tpos = mFirstTpos;

    if (tpos > mLastTpos)
        tpos = mLastTpos;

    Position pos;
    Line * line = mFirstLine;
    Line * last = nullptr;
    pos.org = mFirstTpos;

    while (line != nullptr && tpos >= pos.org + line->len) {
        pos.org += line->len;
        last = line;
        line = line->next;
    }
    if (line == nullptr) {
        pos.x = last->x + last->w;
        pos.y = last->base;
        pos.line = last;
        pos.org -= last->len;
        pos.off = last->len;
    } else {
        pos.x = line->x;
        pos.y = line->base;
        pos.line = line;
        pos.off = tpos - pos.org;
        QFontMetrics m(mCurrentFont);
        int i = pos.org;
        while (i < tpos) {
            char ch = mText->charAt(i); i++;
            pos.x += charWidth(m, ch);
        }
    }
    pos.tpos = pos.org + pos.off;
    return pos;
}

//--------------------------------------------------------------------------
// caret handling
//--------------------------------------------------------------------------

void Viewer::invertCaret(QString color) {
    QMetaObject::invokeMethod(mCanvas, "invertCaret",
                              Q_ARG(QVariant, mCaret.x),
                              Q_ARG(QVariant, mCaret.y),
                              Q_ARG(QVariant, color));
    QMetaObject::invokeMethod(mCanvas, "requestPaint");
}

void Viewer::setCaret(Position pos) {
    removeCaret();
    removeSelection();
    mCaret = pos;
    mCaret.valid = true;
    invertCaret("black");

}

void Viewer::setCaret(int tpos) {
    if (tpos >= mFirstTpos && tpos <= mLastTpos)
        setCaret(Pos(tpos));
    else
        mCaret.valid = false;

}

void Viewer::setCaret(int x, int y) {
    setCaret(Pos(x, y));
}

void Viewer::removeCaret() {
    if (mCaret.valid)
        invertCaret("white");
    mCaret.valid = false;
}


//--------------------------------------------------------------------------
// selection handling
//--------------------------------------------------------------------------

void Viewer::invertSelection(Position beg, Position end)
{
    Line * line = beg.line;
    int x = beg.x;
    int y = line->y;
    int w;
    int h = line->h;
    while (line != end.line) {
        w = line->w + LEFT - x;
        invertSelectionOnCanvas(x, y, w, h);
        line = line->next;
        x = line->x; y = line->y;
    }
    w = end.x - x;
    invertSelectionOnCanvas(x, y, w, h);
}

void Viewer::setSelection(int from, int to)
{
    if (from < to) {
        removeCaret();
        Position beg = Pos(from);
        Position end = Pos(to);
        mSel = Selection(beg, end);
        invertSelection(beg, end);
    }
    else
        mSel.valid = false;
}

void Viewer::removeSelection()
{
    if (mSel.valid)
        invertSelection(mSel.beg, mSel.end);
    mSel.valid = false;
}

//--------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------

void Viewer::OnKeyPressed(int key)
{
    if (mCaret.valid) {
        int pos = mCaret.tpos;
        char ch;
        if (key == Qt::Key_Right) {
            if (mCaret.tpos == mLastTpos) return;
            pos++;
            ch = mText->charAt(pos);
            /*if (ch == '\n')
                pos++;*/
            setCaret(pos);
        }
        else if (key == Qt::Key_Left) {
            if (mCaret.tpos == 0) return;
            pos--;
            ch = mText->charAt(pos);
            /*if (ch == '\n')
                pos--;*/
            setCaret(pos);
        }
        else if (key == Qt::Key_Up) {
            setCaret(mCaret.x, mCaret.y - mCaret.line->h);

        }
        else if (key == Qt::Key_Down) {
            setCaret(mCaret.x, mCaret.y + mCaret.line->h);
        }
        else if (key == Qt::Key_F1) {
            // nothing
        }
    }
}

void Viewer::OnKeyTyped(int key)
{
    bool selection = mSel.valid;

    if (selection) {
        mText->delete_(mSel.beg.tpos, mSel.end.tpos);
        // selection is removed; caret is set at sel.beg.tpos
    }
    if (mCaret.valid) {
        if (key == Qt::Key_Backspace) {
            if (mCaret.tpos > 0 && !selection) {
                int d = 1; //2; //mCaret.off == 0 ? 2 : 1; // CHANGED
                mText->delete_(mCaret.tpos - d, mCaret.tpos);
            }
        }
        else if (key == Qt::Key_Escape) {
            // nothing
        }
        else if (key == Qt::Key_Return) {
            mText->insert(mCaret.tpos, CRLF_);
        }
        else {
            mText->insert(mCaret.tpos, char(key));
        }
        //scrollBar.setValues(firstTpos, 0, 0, text.length()); TODO
    }
}

//--------------------------------------------------------------------------
// mouse handling
//--------------------------------------------------------------------------

void Viewer::OnMouseClicked(int x, int y)
{
    removeCaret();
    removeSelection();
    Position pos = Pos(x, y);
    mSel = Selection(pos, pos);
    mLastPos = pos;
    mLastPos.valid = true;
    qDebug() << "position: " << mSel.beg.tpos << " char: " << mText->charAt(mSel.beg.tpos);
}

void Viewer::OnMouseDragged(int x, int y)
{
    if (mSel.valid == false)
        return;

    Position pos = Pos(x, y);
    if (pos.tpos < mSel.beg.tpos) {
        if (mLastPos.tpos >= mSel.end.tpos) {
            invertSelection(mSel.beg, mLastPos);
            mSel.end = mSel.beg;
        }
        invertSelection(pos, mSel.beg);
        mSel.beg = pos;
    } else if (pos.tpos > mSel.end.tpos) {
        if (mLastPos.tpos <= mSel.beg.tpos) {
            invertSelection(mLastPos, mSel.end);
            mSel.beg = mSel.end;
        }
        invertSelection(mSel.end, pos);
        mSel.end = pos;
    } else if (pos.tpos < mLastPos.tpos) { // beg <= pos <= end; clear pos..end
        invertSelection(pos, mSel.end);
        mSel.end = pos;
    } else if (mLastPos.tpos < pos.tpos) { // beg <= pos <= end; clear beg..pos
        invertSelection(mSel.beg, pos);
        mSel.beg = pos;
    }
    mLastPos = pos;
}

void Viewer::OnMouseReleased()
{
    if (mSel.beg.tpos == mSel.end.tpos)
        setCaret(mSel.beg);
    mLastPos.valid = false;
}

//--------------------------------------------------------------------------
// tab handling
//--------------------------------------------------------------------------

int Viewer::stringWidth(QFontMetrics m, std::string const& s)
{
    std::string s1 = Helpers::ReplaceTabs(s);
    QString qs = QString::fromStdString(s1);
    return m.width(qs);
}

int Viewer::charWidth(QFontMetrics m, char ch)
{
    if (ch == '\t')
        return 4 * m.width(' ');
    else
        return m.width(ch);
}

void Viewer::drawString(std::string const& s, int x, int y, QFont const& font)
{
    QString qs(Helpers::ReplaceTabs(s).c_str());
    QString qfont(Parser::getFontAsString(font).c_str());

    QMetaObject::invokeMethod(mCanvas, "drawString",
                              Q_ARG(QVariant, qs),
                              Q_ARG(QVariant, x),
                              Q_ARG(QVariant, y),
                              Q_ARG(QVariant, qfont));
}

//--------------------------------------------------------------------------
// line handling
//--------------------------------------------------------------------------

Line * Viewer::fill(int top, int bottom, int pos)
{
    // TODO adapt to different font sizes
    QFontMetrics m(mCurrentFont);

    Line * first = nullptr;
    Line * line = nullptr;
    int y = top;
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
        while (ch != '\n' && ch != EOF_) {
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

//--------------------------------------------------------------------------
// text drawing
//--------------------------------------------------------------------------

void Viewer::update(UpdateEvent e)
{
    std::string b;
    QFontMetrics m(mCurrentFont);
    Position pos = mCaret;

    if (e.from == e.to) { // insert
        if (e.from != mCaret.tpos) pos = Pos(e.from);
        int newCarPos = pos.tpos + e.text.length();
        if (e.text.find(CRLF_) != std::string::npos) {
            rebuildFrom(pos);

            //if (pos.y + pos.line->h > getHeight() - BOTTOM)
            //    scrollBar.setValue(firstTpos + firstLine->len); TODO scrollbar
        } else {
            b = pos.line->text;
            b.insert(pos.off, e.text);
            pos.line->text = b;
            pos.line->w += stringWidth(m, e.text);
            pos.line->len += e.text.length();
            mLastTpos += e.text.length();
            repaint(pos.line->x, pos.line->y, getWidth(), pos.line->h+1);
        }
        setCaret(newCarPos);

    }
    else if (e.text == "") { // delete // TODO check nullptr
        if (!mCaret.valid || e.to != mCaret.tpos)
            pos = Pos(e.to);
        int d = e.to - e.from;
        if (pos.off - d < 0) { // delete across lines
            rebuildFrom(Pos(e.from));
        }
        else { // delete within a line
            b = pos.line->text;
            //b.delete(pos.off - d, pos.off); // TODO check
            b.erase(pos.off - d, d);
            pos.line->text = b;
            pos.line->w = stringWidth(m, pos.line->text);
            pos.line->len -= d;
            mLastTpos -= d;
            repaint(pos.line->x, pos.line->y, getWidth(), pos.line->h+1);
        }
        setCaret(e.from);
    }
}

void Viewer::paint()
{
    if (mFirstLine == nullptr) {
        mFirstLine = fill(TOP, getHeight() - BOTTOM, 0);
        mCaret = Pos(0);
        mCaret.valid = true;
    }

    Line * line = mFirstLine;
    while (line != nullptr) {
        drawString(line->text, line->x, line->base, mCurrentFont);
        line = line->next;
    }

    if (mCaret.valid)
        invertCaret("black");

    if (mSel.valid)
        invertSelection(mSel.beg, mSel.end);
}

