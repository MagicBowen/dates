#ifndef H454A7D46_0360_4776_A923_E98CF3108421
#define H454A7D46_0360_4776_A923_E98CF3108421

#include "base/BaseTypes.h"
#include "EventId.h"

namespace SUT
{

struct Sut
{
    static void receive(const EventId, const void* data, const U32 length);
};

}

#endif
