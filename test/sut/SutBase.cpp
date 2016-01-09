#include "sut/SutBase.h"
#include "base/log.h"
#include "Events.h"
#include <string.h>

SUT_NS_BEGIN

//////////////////////////////////////////////////////////
namespace
{
    template<typename DEST>
    const DEST& cast_event(const void *data)
    {
        return *(reinterpret_cast<const DEST*>(data));
    }
}

//////////////////////////////////////////////////////////
void SutBase::receive(const EventId id, const void* data, const U32 length)
{
    switch(id)
    {
    case EVENT_HELLO:
        handleHello(cast_event<Hello>(data));
        break;
    case EVENT_PING:
        handlePing(cast_event<Ping>(data));
        break;
    default:
        ERR_LOG("SUT received unrecognized event(%d)", id);
    }
}

//////////////////////////////////////////////////////////
void SutBase::handleHello(const Hello& event)
{
    if(strcmp(event.data, "Hey!") != 0)  return;

    Hello rsp;
    rsp.header.id = EVENT_HELLO;
    strcpy(rsp.data, "Who are you?");
    send(EVENT_HELLO, &rsp, sizeof(rsp));
}

//////////////////////////////////////////////////////////
void SutBase::handlePing(const Ping& event)
{
    Pong pong;
    pong.header.id = EVENT_PONG;
    pong.reply = event.request;
    send(EVENT_PONG, &pong, sizeof(pong));
}

SUT_NS_END
