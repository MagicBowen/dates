#ifndef HBA112C56_26EB_45E0_90C4_A258C273470C
#define HBA112C56_26EB_45E0_90C4_A258C273470C

#include <core/MsgTransit.h>

DATES_NS_BEGIN

struct MsgQueue;
struct MsgListener;
struct MsgSender;

struct FakeMsgTransit : MsgTransit
{
private:
    OVERRIDE(void sendMsg(const char* msgName, const RawMsg&) const);
    OVERRIDE(RawMsg recvMsg(const char* msgName, const MsgId) const);

private:
    USE_ROLE(MsgQueue);
    USE_ROLE(MsgListener);
    USE_ROLE(MsgSender);
};

DATES_NS_END

#endif
