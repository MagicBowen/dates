#ifndef HB81DBD0C_C4BA_4630_8BD0_57CB536D8208
#define HB81DBD0C_C4BA_4630_8BD0_57CB536D8208

#include "details/dates.h"
#include "base/Role.h"

DATES_NS_BEGIN

struct TaggedMsg;

DEFINE_ROLE(MsgReceiver)
{
    ABSTRACT(void recv(const TaggedMsg&));
};

DATES_NS_END

#endif
