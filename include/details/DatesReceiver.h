#ifndef HB81DBD0C_C4BA_4630_8BD0_57CB536D8208
#define HB81DBD0C_C4BA_4630_8BD0_57CB536D8208

#include "details/dates.h"

DATES_NS_BEGIN

struct RawMsg;

struct DatesReceiver
{
    static void recv(const RawMsg&);
};

DATES_NS_END

#endif
