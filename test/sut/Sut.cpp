#include "sut/Sut.h"
#include "base/log.h"
#include <string.h>

namespace SUT
{

Sut& Sut::getInstance()
{
    static Sut instance;
    return instance;
}

void Sut::receive(const MsgId id, const void* data, const U32 length)
{
    switch(id)
    {
    case EVENT_HELLO:
        Hello msg;
        msg.header.id = EVENT_HELLO;
        strcpy(msg.data, "Who are you?");
        send(EVENT_HELLO, &msg, sizeof(msg));
        break;

    case EVENT_REQUEST:
        break;

    default:
        ERR_LOG("SUT received unrecognized msg(%d)", id);
    }
}

}
