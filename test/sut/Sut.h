#ifndef H454A7D46_0360_4776_A923_E98CF3108421
#define H454A7D46_0360_4776_A923_E98CF3108421

#include "base/BaseTypes.h"
#include "sut/Msgs.h"

USING_DATES_NS

namespace SUT
{

void send(const MsgId, const void* data, const U32 length);

struct Sut
{
    static Sut& getInstance();
    void receive(const MsgId, const void* data, const U32 length);
};

}

#endif
