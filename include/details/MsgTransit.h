#ifndef HB33CBBF0_243C_42AD_838D_479AEDCD891F
#define HB33CBBF0_243C_42AD_838D_479AEDCD891F

#include "details/MsgId.h"
#include "base/Role.h"

DATES_NS_BEGIN

struct TaggedMsg;

DEFINE_ROLE(MsgTransit)
{
    ABSTRACT(void sendMsg(const char* msgName, const TaggedMsg&) const);
    ABSTRACT(TaggedMsg& recvMsg(const char* msgName, const MsgId id) const);
};

DATES_NS_END

#endif
