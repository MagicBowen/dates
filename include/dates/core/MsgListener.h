#ifndef H18F78CFE_4245_4B74_A331_726361D95A6B
#define H18F78CFE_4245_4B74_A331_726361D95A6B

#include <dates/core/MsgId.h>
#include <ccinfra/dci/Role.h>

DATES_NS_BEGIN

DEFINE_ROLE(MsgListener)
{
    ABSTRACT(void onMsgMiss(const char* msgName, const MsgId) const);
    ABSTRACT(void onMsgSend(const char* msgName, const MsgId) const);
    ABSTRACT(void onMsgRecv(const char* msgname, const MsgId) const);
};

DATES_NS_END

#endif
