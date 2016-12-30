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

    // GUI event handlers
    Q_INVOKABLE bool OnLoadFile(QString str);
    Q_INVOKABLE bool OnSaveFile(QString file);
    Q_INVOKABLE void OnCut();
    Q_INVOKABLE void OnCopy();
    Q_INVOKABLE void OnPaste();
    Q_INVOKABLE void OnFind(QString str);
    Q_INVOKABLE void OnFontChanged(QString font);
    Q_INVOKABLE void OnFontSizeChanged(int size);
    Q_INVOKABLE void OnFontStyleChanged(bool bold, bool italic, bool underlined);


    // mouse handling
    Q_INVOKABLE void OnMouseClicked(int x, int y);
    Q_INVOKABLE void OnMouseDragged(int x, int y);
    Q_INVOKABLE void OnMouseReleased();

    // keyboard handling
    Q_INVOKABLE void OnKeyPressed(int key);
    Q_INVOKABLE void OnKeyTyped(int key);


    // TODO: scrolling
    // TODO: position handling
    // TODO: caret handling
    // TODO: selection handling
    // TODO: tab handling
    // TODO: line handling

    Q_INVOKABLE QString testToGui();
    void testFromGui();

    // TODO: text drawing
    virtual void update(UpdateEvent e) override;
    Q_INVOKABLE void paint();

private:

    QObject * mCanvas;

    // constants
    const size_t        TOP = 5;    // top margin
    const size_t        BOTTOM = 5; // bottom margin
    const size_t        LEFT = 5;   // left margin
    const char          EOF_ = '\0';
    const std::string   CRLF = "\r\n";

    // members
    PieceListText * mText;
    Line * mFirstLine;       // the lines in this viewer
    size_t mFirstTpos;       // first text position in this viewer
    size_t mLastTpos;        // last text position in this viewer
    Selection * mSel;
    Position * mCaret;
    Position * mLastPos;     // last mouse position: used during mouse dragging
    //Graphics g;

    // functions
    Line * fill(size_t top, size_t bottom, size_t pos);
    void drawString(std::string const& s, size_t x, size_t y, std::string const& font, int style);

};

#endif // VIEWER_H
