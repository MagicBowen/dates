#ifndef H454A7D46_0360_4776_A923_E98CF3108421
#define H454A7D46_0360_4776_A923_E98CF3108421

#include "sut/SutBase.h"
#include "details/dates.h"

DATES_FWD_DECL(MsgReceiver);

SUT_NS_BEGIN

struct SyncSut : SutBase
{
    SyncSut(MsgReceiver&);

private:
    OVERRIDE(void doSend(const void* data, const U32 length));

private:
    MsgReceiver& receiver;
};

SUT_NS_END

#endif
