#ifndef HE02B3F39_D810_4021_AC76_C4DE54FDB155
#define HE02B3F39_D810_4021_AC76_C4DE54FDB155

#include "details/dates.h"
#include "base/EventId.h"

struct Event;

DATES_NS_BEGIN

struct DatesSender
{
    static void send(const Event&);
};

DATES_NS_END

#endif
