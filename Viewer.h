#ifndef VIEWER_H
#define VIEWER_H

#include "PieceListText.h"
#include "UpdateEvent.h"
#include <QObject>
#include <QString>
#include <QKeyEvent>

class Viewer : public QObject, public UpdateEventListener
{
    Q_OBJECT

public:
    explicit Viewer(PieceListText * text = 0, QObject * canvas = 0);

    // TODO: scrolling
    // TODO: position handling
    // TODO: caret handling
    // TODO: selection handling

    // TODO. mouse handling
    Q_INVOKABLE void OnMouseClicked(int x, int y);
    Q_INVOKABLE void OnMouseDragged(int x, int y);
    Q_INVOKABLE void OnMouseReleased();

    // TODO: tab handling
    // TODO: line handling

    // TODO: keyboard handling
    Q_INVOKABLE void OnKeyPressed(int key);
    Q_INVOKABLE void OnKeyTyped(int key);


    Q_INVOKABLE QString testToGui();
    void testFromGui();

    // TODO: text drawing
    virtual void update(UpdateEvent e) override;

private:
    PieceListText * mText;
    QObject * mCanvas;
};

#endif // VIEWER_H
