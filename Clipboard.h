#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <PieceListText.h>

class ClipBoard
{
public:
    ClipBoard();
    void copyToClipBoard(PieceListText * text, int from, int to);
    void cutToClipBoard(PieceListText * text, int from, int to);
    void pasteFromClipBoard(PieceListText * text, int pos);

private:
    Piece * mFirstPiece;
    void deleteClipBoard();
    void adjustValues(int & from, int & to);
};

#endif // CLIPBOARD_H
