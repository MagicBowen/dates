#include "FakeSystemBase.h"
#include "base/log.h"
#include <string.h>
#include "DatesFrame.h"
#include "RawMsg.h"

DATES_NS_BEGIN

void FakeSystemBase::onTimeOut(const char* msgName) const
{
    ERR_LOG("System[%s] wait msg[%s] timeout!!!", getName(), msgName);
    throw("Fatal: receive msg timeout!");
}

void FakeSystemBase::onMsgSend(const char* msgName, const MsgId msgId) const
{
    INFO_LOG("System[%s] send msg[%s : %d]!", getName(), msgName, msgId);
}

void FakeSystemBase::onMsgRecv(const char* msgName, const MsgId msgId) const
{
    INFO_LOG("System[%s] recv msg[%s : %d]!", getName(), msgName, msgId);
}

void FakeSystemBase::send(const MsgId id, const U32 length, void* msg) const
{
    DatesFrame::getInstance().send(id, RawMsg(length, (U8*)msg));
}

DATES_NS_END
