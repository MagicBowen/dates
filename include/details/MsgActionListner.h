#ifndef H18F78CFE_4245_4B74_A331_726361D95A6B
#define H18F78CFE_4245_4B74_A331_726361D95A6B

#include "details/dates.h"
#include "details/MsgId.h"
#include "base/Role.h"
#include "base/BaseTypes.h"

DATES_NS_BEGIN

struct RawMsg;
struct FakeSystemInfo;

DEFINE_ROLE(MsgActionListner)
{
    void onTimeOut(const char* msgName) const;
    void onMsgSend(const char* msgName, const MsgId) const;
    void onMsgRecv(const char* msgname, const MsgId) const;
    void send(const RawMsg&) const;

private:
    USE_ROLE(FakeSystemInfo);
};

DATES_NS_END

#endif
