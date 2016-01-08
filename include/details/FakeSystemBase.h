#ifndef H18F78CFE_4245_4B74_A331_726361D95A6B
#define H18F78CFE_4245_4B74_A331_726361D95A6B

#include "base/Role.h"
#include "base/BaseTypes.h"
#include "details/MsgId.h"

DATES_NS_BEGIN

DEFINE_ROLE(FakeSystemBase)
{
    void onTimeOut(const char* msgName) const;
    void onMsgSend(const char* msgName, const MsgId) const;
    void onMsgRecv(const char* msgname, const MsgId) const;
    void send(const MsgId, const U32 length, void* msg) const;

private:
    ABSTRACT(const char* getName() const);
};

DATES_NS_END

#endif
