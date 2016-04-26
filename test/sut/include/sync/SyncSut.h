#ifndef H454A7D46_0360_4776_A923_E98CF3108421
#define H454A7D46_0360_4776_A923_E98CF3108421

#include <common/SutBase.h>
#include "core/dates.h"

DATES_FWD_DECL(MsgQueue);

SUT_NS_BEGIN

struct SyncSut : SutBase
{
    SyncSut(MsgQueue&);

private:
    OVERRIDE(void doSend(const void* data, const U32 length));

private:
    MsgQueue& msgQueue;
};

SUT_NS_END

#endif
