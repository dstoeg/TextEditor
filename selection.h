#ifndef SELECTION_H
#define SELECTION_H

#include "Position.h"

class Selection
{
public:
    Position beg;
    Position end;
    bool valid;
    Selection (Position a, Position b) { beg = a; end = b; valid = true;}
    Selection () { valid = false;}
};

#endif // SELECTION_H
