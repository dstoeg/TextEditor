#include "UpdateEvent.h"

UpdateEvent::UpdateEvent(int a, int b, std::string const& t)
{
    from = a;
    to = b;
    text = t;
}
