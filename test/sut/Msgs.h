#ifndef HE88AAE58_7D7F_4533_9909_AF9C0360C0AC
#define HE88AAE58_7D7F_4533_9909_AF9C0360C0AC

#include "base/BaseTypes.h"
#include "MsgId.h"

using MsgId = U16;

namespace SUT
{
    const MsgId EVENT_HELLO = 0;
    const MsgId EVENT_REQUEST = 1;
    const MsgId EVENT_REPLY = 2;

    struct Header
    {
        MsgId id;
    };

    struct Hello
    {
        Header header;
        char   data[16];
    };

    struct Request
    {
        Header header;
        U32 cmd;
    };

    struct Reply
    {
        Header header;
        U32 status;
    };
}

#endif
