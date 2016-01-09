#ifndef H454A7D46_0360_4776_A923_E98CF3108421
#define H454A7D46_0360_4776_A923_E98CF3108421

#include "sut/SutBase.h"

SUT_NS_BEGIN

struct SyncSut : SutBase
{
private:
    OVERRIDE(void doSend(const void* data, const U32 length));
};

SUT_NS_END

#endif
