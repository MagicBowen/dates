#include "sut/Sut.h"
#include "base/log.h"
#include "Events.h"
#include <string.h>

namespace SUT
{

extern void send(const EventId, const void* data, const U32 length);

void Sut::receive(const EventId id, const void* data, const U32 length)
{
    switch(id)
    {
    case EVENT_HELLO:
        Hello msg;
        msg.header.id = EVENT_HELLO;
        strcpy(msg.data, "Who are you?");
        send(EVENT_HELLO, &msg, sizeof(msg));
        break;

    case EVENT_PING:
        Pong pong;
        pong.reply = ((const Ping*)(data))->request;
        send(EVENT_PONG, &pong, sizeof(pong));
        break;

    default:
        ERR_LOG("SUT received unrecognized msg(%d)", id);
    }
}

}
