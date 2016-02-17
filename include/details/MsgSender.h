#ifndef H41376541_41EB_4431_98EA_7FA140ECF56E
#define H41376541_41EB_4431_98EA_7FA140ECF56E

#include "details/dates.h"
#include "base/Role.h"

DATES_NS_BEGIN

struct TaggedMsg;

DEFINE_ROLE(MsgSender)
{
    ABSTRACT(void send(const TaggedMsg&));
};

DATES_NS_END

#endif
