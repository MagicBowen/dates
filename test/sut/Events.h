#ifndef HE88AAE58_7D7F_4533_9909_AF9C0360C0AC
#define HE88AAE58_7D7F_4533_9909_AF9C0360C0AC

#include "sut_ns.h"
#include "base/BaseTypes.h"
#include "EventId.h"

SUT_NS_BEGIN

const EventId EVENT_HELLO = 0;
const EventId EVENT_PING = 1;
const EventId EVENT_PONG = 2;

struct Header
{
    EventId id;
};

struct Hello
{
    Header header;
    char   data[16];
};

struct Ping
{
    Header header;
    U32 request;
};

struct Pong
{
    Header header;
    U32 reply;
};

SUT_NS_END

#endif
