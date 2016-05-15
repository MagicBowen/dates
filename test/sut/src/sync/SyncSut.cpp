#include <sync/SyncSut.h>
#include <sync/SyncMsgs.h>
#include <dates/core/RawMsg.h>
#include <dates/core/MsgQueue.h>
#include <ccinfra/log/log.h>
#include <string.h>

SUT_NS_BEGIN

SyncSut::SyncSut(MsgQueue& msgQueue)
: msgQueue(msgQueue)
{
}

//////////////////////////////////////////////////////////
Status SyncSut::receive(const MsgId id, const void* data, const U32 length)
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
        return SUCCESS;
    default:
        ERR_LOG("Error: SUT recv unrecognized msg[%d]", id);
    }

    return FAILURE;
}

void SyncSut::send(const MsgId id, const void* data, const U32 length)
{
    INFO_LOG("SUT send msg[%d]", id);

    ((Header*)data)->id = id;
    doSend(data, length);
}

//////////////////////////////////////////////////////////
void SyncSut::handleHello(const Hello& event)
{
    if(strcmp(event.data, "Hey!") != 0)  return;

    Hello rsp;
    strcpy(rsp.data, "Who are you?");
    send(EVENT_HELLO, &rsp, sizeof(rsp));
}

//////////////////////////////////////////////////////////
void SyncSut::handlePing(const Ping& event)
{
    Pong pong;
    pong.reply = event.request;
    send(EVENT_PONG, &pong, sizeof(pong));
}

//////////////////////////////////////////////////////////
void SyncSut::handleTerminate(const Terminate& event)
{
    send(EVENT_TERMINATE, &event, sizeof(event));
}


void SyncSut::doSend(const void* data, const U32 length)
{
    RawMsg msg(((Header*)data)->id, length);
    memcpy(msg.getMsg(), data, length);
    msgQueue.insert(std::move(msg));
}

SUT_NS_END
