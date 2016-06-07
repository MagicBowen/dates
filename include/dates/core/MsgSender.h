#ifndef H41376541_41EB_4431_98EA_7FA140ECF56E
#define H41376541_41EB_4431_98EA_7FA140ECF56E

#include <dates/core/dates.h>
#include <ccinfra/dci/Role.h>
#include <ccinfra/base/Keywords.h>

DATES_NS_BEGIN

struct RawMsg;

DEFINE_ROLE(MsgSender)
{
    ABSTRACT(void send(const RawMsg&));
};

DATES_NS_END

#endif
