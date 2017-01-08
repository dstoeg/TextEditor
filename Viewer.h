#ifndef VIEWER_H
#define VIEWER_H

#include "PieceListText.h"
#include "UpdateEvent.h"
#include "Selection.h"
#include "Clipboard.h"
#include <QObject>
#include <QString>
#include <QKeyEvent>


class Viewer : public QObject, public UpdateEventListener
{
    Q_OBJECT

public:
    explicit Viewer(QObject * canvas = 0);

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
    Q_INVOKABLE void OnDoubleClick(int x, int y);
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
    void drawLine(Line * line);

private:

    //--------------------------------------------------------------------------
    // selection handling
    //--------------------------------------------------------------------------
    void invertSelection(Position beg, Position end);
    void setSelection(int from, int to);
    void removeSelection();

    //--------------------------------------------------------------------------
    // position handling
    //--------------------------------------------------------------------------
    Position Pos(int x, int y);
    Position Pos(int tpos);

    //--------------------------------------------------------------------------
    // line handling
    //--------------------------------------------------------------------------
    Line * fill(int top, int bottom, int pos);
    void rebuildFrom(Position pos);

    //--------------------------------------------------------------------------
    // caret handling
    //--------------------------------------------------------------------------
    void invertCaret(QString color);
    void setCaret(Position pos);
    void setCaret(int tpos);
    void setCaret(int x, int y);
    void removeCaret();

    //--------------------------------------------------------------------------
    // tab handling
    //--------------------------------------------------------------------------
    int stringWidth(QFontMetrics m, std::string const& s);
    int charWidth(QFontMetrics m, char ch);
    void drawString(std::string const& s, int x, int y, QFont const& font);

    //--------------------------------------------------------------------------
    // delegates to canvas
    //--------------------------------------------------------------------------
    int getHeight();
    int getWidth();
    void repaint(int x, int y, int width, int height);
    void invertSelectionOnCanvas(int x, int y, int width, int height);

    //--------------------------------------------------------------------------
    // members
    //--------------------------------------------------------------------------
    QObject * mCanvas;
    QFont mCurrentFont;
    PieceListText * mText;
    Line * mFirstLine;       // the lines in this viewer
    int mFirstTpos;       // first text position in this viewer
    int mLastTpos;        // last text position in this viewer
    Selection mSel;
    Position mCaret;
    Position mLastPos;     // last mouse position: used during mouse dragging
    ClipBoard mClipBoard;


    //--------------------------------------------------------------------------
    // constants
    //--------------------------------------------------------------------------
    const int        TOP = 10;    // top margin
    const int        BOTTOM = 10; // bottom margin
    const int        LEFT = 10;   // left margin
    const char       EOF_ = '\0';
    //const std::string   CRLF_ = "\r\n";
    const char CRLF_ = '\n';


    //--------------------------------------------------------------------------
    // font metrics calculations
    //--------------------------------------------------------------------------
    int getLineWidth(Line * line);
    int getLineHeight(Line * line);
    int getLineAscent(Line * line);
};

#endif // VIEWER_H
