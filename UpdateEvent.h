#ifndef UPDATEEVENT_H
#define UPDATEEVENT_H

#include <string>


class UpdateEvent
{
public:
    int from;
    int to;
    std::string text;
    UpdateEvent(int a, int b, std::string const& t);
};

class UpdateEventListener
{
public:
    virtual void update(UpdateEvent e) = 0;
};

#endif // UPDATEEVENT_H
