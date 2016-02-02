#ifndef HE02B3F39_D810_4021_AC76_C4DE54FDB155
#define HE02B3F39_D810_4021_AC76_C4DE54FDB155

#include "details/dates.h"
#include "base/Role.h"

DATES_NS_BEGIN

struct RawMsg;

DEFINE_ROLE(DatesSender)
{
    ABSTRACT(void send(const RawMsg&));
};

DATES_NS_END

#endif
