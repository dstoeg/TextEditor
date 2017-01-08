#ifndef LINE_H
#define LINE_H

#include "Piece.h"

class Line
{
public:
    std::string text;   // text of this line
    int len;            // length of this line (including CRLF)
    int x;              // top left corner
    int y;
    int w;              // width
    int h;              // height
    int base;           // base line
    Line * prev;
    Line * next;
    Piece * firstPiece;
};

#endif // LINE_H
