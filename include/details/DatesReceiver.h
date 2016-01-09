#ifndef HB81DBD0C_C4BA_4630_8BD0_57CB536D8208
#define HB81DBD0C_C4BA_4630_8BD0_57CB536D8208

#include "details/dates.h"

struct Event;

DATES_NS_BEGIN

struct DatesReceiver
{
    static void recv(const Event&);
};

DATES_NS_END

#endif
