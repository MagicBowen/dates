#include <common/SutBase.h>
#include "base/MsgCast.h"
#include "base/log.h"
#include <common/Msgs.h>
#include <string.h>

SUT_NS_BEGIN

//////////////////////////////////////////////////////////
Status SutBase::receive(const MsgId id, const void* data, const U32 length)
{
    INFO_LOG("SUT recv msg[%d]", id);

    switch(id)
    {
    case EVENT_HELLO:
        handleHello(msg_cast<Hello>(data));
        return SUCCESS;
    case EVENT_PING:
        handlePing(msg_cast<Ping>(data));
        return SUCCESS;
    case EVENT_TERMINATE:
        handleTerminate(msg_cast<Terminate>(data));
        break;
    default:
        ERR_LOG("Error: SUT recv unrecognized msg[%d]", id);
    }

    return FAILURE;
}

void SutBase::send(const MsgId id, const void* data, const U32 length)
{
    INFO_LOG("SUT send msg[%d]", id);

    ((Header*)data)->id = id;
    doSend(data, length);
}

//////////////////////////////////////////////////////////
void SutBase::handleHello(const Hello& event)
{
    if(strcmp(event.data, "Hey!") != 0)  return;

    Hello rsp;
    strcpy(rsp.data, "Who are you?");
    send(EVENT_HELLO, &rsp, sizeof(rsp));
}

//////////////////////////////////////////////////////////
void SutBase::handlePing(const Ping& event)
{
    Pong pong;
    pong.reply = event.request;
    send(EVENT_PONG, &pong, sizeof(pong));
}

//////////////////////////////////////////////////////////
void SutBase::handleTerminate(const Terminate& event)
{
    send(EVENT_TERMINATE, &event, sizeof(event));
}

SUT_NS_END
