#ifndef HE88AAE58_7D7F_4533_9909_AF9C0360C0AC
#define HE88AAE58_7D7F_4533_9909_AF9C0360C0AC

#include <common/sut.h>
#include <ccinfra/base/BaseTypes.h>
#include <dates/core/MsgId.h>

USING_DATES_NS
SUT_NS_BEGIN

const MsgId EVENT_HELLO = 0;
const MsgId EVENT_PING = 1;
const MsgId EVENT_PONG = 2;
const MsgId EVENT_TERMINATE = 3;

struct Header
{
    MsgId id;
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

struct Terminate
{
    Header header;
};

SUT_NS_END

#endif
