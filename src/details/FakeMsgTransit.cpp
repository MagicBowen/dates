#include <details/FakeMsgTransit.h>
#include "details/MsgQueue.h"
#include "details/MsgListener.h"
#include "details/MsgSender.h"
#include <details/TaggedMsg.h>
#include "base/NullPtr.h"

DATES_NS_BEGIN

TaggedMsg FakeMsgTransit::recvMsg(const char* msgName, const MsgId id) const
{
    TaggedMsg msg;

    auto matcher = [id](const TaggedMsg& msg){return id == msg.getId();};

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

void FakeMsgTransit::sendMsg(const char* msgName, const TaggedMsg& msg) const
{
    ROLE(MsgListener).onMsgSend(msgName, msg.getId());
    ROLE(MsgSender).send(msg);
}

DATES_NS_END
