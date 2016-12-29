#ifndef SELECTION_H
#define SELECTION_H

#include "Position.h"

class Selection
{
public:
    Position beg;
    Position end;
    Selection (Position a, Position b) { beg = a; end = b; }
};

#endif // SELECTION_H
