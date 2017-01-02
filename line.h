#ifndef LINE_H
#define LINE_H

#include <string>

class Line
{
public:
    std::string text;   // text of this line
    size_t len;         // length of this line (including CRLF)
    size_t x;           // top left corner
    size_t y;
    size_t w;           // width
    size_t h;           // height
    size_t base;        // base line
    Line * prev;
    Line * next;
};

#endif // LINE_H
