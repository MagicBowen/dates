#ifndef HA242D5BE_DC7B_4C30_BC85_4418AF9F474F
#define HA242D5BE_DC7B_4C30_BC85_4418AF9F474F

#include "details/dates.h"
#include "base/Role.h"

DATES_NS_BEGIN

struct DatesSender;
struct DatesReceiver;
struct MsgQueue;

DEFINE_ROLE(Runtime)
{
    HAS_ROLE(DatesSender);
    HAS_ROLE(DatesReceiver);
    HAS_ROLE(MsgQueue);
};

DATES_NS_END

#endif
