#include "Clipboard.h"
#include <algorithm>

ClipBoard::ClipBoard()
{
    mFirstPiece = nullptr;
}

void ClipBoard::copyToClipBoard(PieceListText * text, int from, int to)
{
    adjustValues(from, to);
    deleteClipBoard();
    Piece * a = text->split(from);
    Piece * b = text->split(to);

    Piece * original = a->getNext();
    mFirstPiece = original->getDeepCopy();
    Piece * copy = mFirstPiece;

    while (original != nullptr && original != b)
    {
        copy->setNext(original->getNext()->getDeepCopy());
        original = original->getNext();
        copy = copy->getNext();
    }
    copy->setNext(nullptr);
}

void ClipBoard::cutToClipBoard(PieceListText * text, int from, int to)
{
    copyToClipBoard(text, from, to);
    text->delete_(from, to);
}

void ClipBoard::pasteFromClipBoard(PieceListText * text, int pos)
{
    if (mFirstPiece == nullptr)
        return;

    Piece * piece = mFirstPiece;
    while(piece != nullptr)
    {
        text->insert(pos, piece->getText(), piece->getFont());
        pos += piece->getLength();
        piece = piece->getNext();
    }
}

void ClipBoard::deleteClipBoard()
{
    Piece * p = mFirstPiece;
    Piece * tmp = nullptr;
    while (p != nullptr)
    {
        tmp = p;
        p = p->getNext();
        delete tmp; tmp = nullptr;

    }
    mFirstPiece = nullptr;
}

void ClipBoard::adjustValues(int & from, int & to)
{
    int max = std::max(from, to);
    int min = std::min(from, to);
    from = min;
    to = max;
}
