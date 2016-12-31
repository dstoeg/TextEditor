#ifndef VIEWER_H
#define VIEWER_H

#include "PieceListText.h"
#include "UpdateEvent.h"
#include "Selection.h"
#include <QObject>
#include <QString>
#include <QKeyEvent>


class Viewer : public QObject, public UpdateEventListener
{
    Q_OBJECT

public:
    explicit Viewer(PieceListText * text = 0, QObject * canvas = 0);

    //--------------------------------------------------------------------------
    // GUI handling
    //--------------------------------------------------------------------------
    Q_INVOKABLE bool OnLoadFile(QString str);
    Q_INVOKABLE bool OnSaveFile(QString file);
    Q_INVOKABLE void OnCut();
    Q_INVOKABLE void OnCopy();
    Q_INVOKABLE void OnPaste();
    Q_INVOKABLE void OnFind(QString str);
    Q_INVOKABLE void OnFontChanged(QString font);
    Q_INVOKABLE void OnFontSizeChanged(int size);
    Q_INVOKABLE void OnFontStyleChanged(bool bold, bool italic, bool underlined);

    //--------------------------------------------------------------------------
    // mouse handling
    //--------------------------------------------------------------------------
    Q_INVOKABLE void OnMouseClicked(int x, int y);
    Q_INVOKABLE void OnMouseDragged(int x, int y);
    Q_INVOKABLE void OnMouseReleased();

    //--------------------------------------------------------------------------
    // key handling
    //--------------------------------------------------------------------------
    Q_INVOKABLE void OnKeyPressed(int key);
    Q_INVOKABLE void OnKeyTyped(int key);


    //--------------------------------------------------------------------------
    // text drawing
    //--------------------------------------------------------------------------
    virtual void update(UpdateEvent e) override;
    Q_INVOKABLE void paint();

private:

    //--------------------------------------------------------------------------
    // selection handling
    //--------------------------------------------------------------------------
    void invertSelection(Position beg, Position end);
    void setSelection(size_t from, size_t to);
    void removeSelection();

    //--------------------------------------------------------------------------
    // position handling
    //--------------------------------------------------------------------------
    Position Pos(size_t x, size_t y);
    Position Pos(size_t tpos);

    //--------------------------------------------------------------------------
    // line handling
    //--------------------------------------------------------------------------
    Line * fill(size_t top, size_t bottom, size_t pos);
    void rebuildFrom(Position pos);

    //--------------------------------------------------------------------------
    // caret handling
    //--------------------------------------------------------------------------
    void invertCaret();
    void setCaret(Position pos);
    void setCaret(size_t tpos);
    void setCaret(size_t x, size_t y);
    void removeCaret();

    //--------------------------------------------------------------------------
    // tab handling
    //--------------------------------------------------------------------------
    size_t stringWidth(QFontMetrics m, std::string const& s);
    size_t charWidth(QFontMetrics m, char ch);
    void drawString(std::string const& s, size_t x, size_t y, QFont const& font);

    //--------------------------------------------------------------------------
    // delegates to canvas
    //--------------------------------------------------------------------------
    size_t getHeight();
    size_t getWidth();
    void repaint(size_t x, size_t y, size_t width, size_t height);

    //--------------------------------------------------------------------------
    // members
    //--------------------------------------------------------------------------
    QObject * mCanvas;
    QFont mCurrentFont;
    PieceListText * mText;
    Line * mFirstLine;       // the lines in this viewer
    size_t mFirstTpos;       // first text position in this viewer
    size_t mLastTpos;        // last text position in this viewer
    Selection mSel;
    Position mCaret;
    bool mCaretVisible;
    Position mLastPos;     // last mouse position: used during mouse dragging

    //--------------------------------------------------------------------------
    // constants
    //--------------------------------------------------------------------------
    const size_t        TOP = 5;    // top margin
    const size_t        BOTTOM = 5; // bottom margin
    const size_t        LEFT = 5;   // left margin
    const char          EOF_ = '\0';
    const std::string   CRLF = "\r\n";
};

#endif // VIEWER_H
