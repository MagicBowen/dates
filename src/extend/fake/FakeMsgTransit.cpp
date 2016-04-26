#include <extend/fake/FakeMsgTransit.h>
#include <core/MsgQueue.h>
#include <core/MsgListener.h>
#include <core/MsgSender.h>
#include <core/RawMsg.h>
#include "base/NullPtr.h"

DATES_NS_BEGIN

RawMsg FakeMsgTransit::recvMsg(const char* msgName, const MsgId id) const
{
    RawMsg msg;

    auto matcher = [id](const RawMsg& msg){return id == msg.getId();};

    if(ROLE(MsgQueue).fetch(matcher, msg))
    {
        ROLE(MsgListener).onMsgRecv(msgName, id);
    }
    else
    {
        ROLE(MsgListener).onMsgMiss(msgName, id);
    }

    return std::move(msg);
}

void FakeMsgTransit::sendMsg(const char* msgName, const RawMsg& msg) const
{
    ROLE(MsgListener).onMsgSend(msgName, msg.getId());
    ROLE(MsgSender).send(msg);
}

DATES_NS_END
