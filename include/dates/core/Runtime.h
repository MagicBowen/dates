#ifndef HA242D5BE_DC7B_4C30_BC85_4418AF9F474F
#define HA242D5BE_DC7B_4C30_BC85_4418AF9F474F

#include <dates/core/dates.h>
#include <ccinfra/dci/Role.h>

DATES_NS_BEGIN

struct MsgSender;
struct MsgQueue;

DEFINE_ROLE(Runtime)
{
    HAS_ROLE(MsgSender);
    HAS_ROLE(MsgQueue);
};

DATES_NS_END

#endif
