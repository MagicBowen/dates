#include "details/FakeMsgUtils.h"
#include "details/MsgQueue.h"
#include "details/MsgListener.h"
#include "details/MsgSender.h"
#include "details/RawMsg.h"
#include "base/NullPtr.h"

DATES_NS_BEGIN

RawMsg& FakeMsgUtils::recvMsg(const char* msgName, const MsgId id) const
{
    static RawMsg msg;

    if(ROLE(MsgQueue).fetch([=](const RawMsg& msg){return id == msg.getId();}, msg))
    {
        ROLE(MsgListener).onMsgRecv(msgName, id);
    }
    else
    {
        ROLE(MsgListener).onMsgMiss(msgName, id);
    }

    return msg;
}

void FakeMsgUtils::sendMsg(const char* msgName, const RawMsg& msg) const
{
    ROLE(MsgListener).onMsgSend(msgName, msg.getId());
    ROLE(MsgSender).send(msg);
}

DATES_NS_END
