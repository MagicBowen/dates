#ifndef HB33CBBF0_243C_42AD_838D_479AEDCD891F
#define HB33CBBF0_243C_42AD_838D_479AEDCD891F

#include "base/MsgId.h"
#include "base/Role.h"

DATES_NS_BEGIN

struct RawMsg;

DEFINE_ROLE(MsgTransit)
{
    ABSTRACT(void sendMsg(const char* msgName, const RawMsg&) const);
    ABSTRACT(RawMsg recvMsg(const char* msgName, const MsgId id) const);
};

DATES_NS_END

#endif
