#include "sut/Sut.h"
#include "base/log.h"
#include "Events.h"
#include <string.h>

SUT_NS_BEGIN

extern void send(const EventId, const void* data, const U32 length);

namespace
{
    void handleHello(const Hello& event)
    {
        if(strcmp(event.data, "Hi") != 0)  return;

        Hello rsp;
        rsp.header.id = EVENT_HELLO;

        strcpy(rsp.data, "Who are you?");

        send(EVENT_HELLO, &rsp, sizeof(rsp));
    }

    void handlePing(const Ping& event)
    {
        Pong pong;
        pong.reply = event.request;
        send(EVENT_PONG, &pong, sizeof(pong));
    }
}

//////////////////////////////////////////////////////////
#define EVENT_HANDLE_BEGIN() switch(id){
#define EVENT_HANDLE_END()                      \
default: ERR_LOG("SUT received unrecognized msg(%d)", id); }
#define EVENT_HANDLE(ID, EVENT)                 \
case ID: handle##EVENT(*(const EVENT*)(data));  \
break;

//////////////////////////////////////////////////////////
void Sut::receive(const EventId id, const void* data, const U32 length)
{
    EVENT_HANDLE_BEGIN()
        EVENT_HANDLE(EVENT_HELLO, Hello)
        EVENT_HANDLE(EVENT_PING,  Ping)
    EVENT_HANDLE_END()
}

SUT_NS_END
