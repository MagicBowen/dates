#include "details/FakeSystemBase.h"
#include "details/DatesSender.h"
#include "details/RawMsg.h"
#include "base/log.h"

DATES_NS_BEGIN

void FakeSystemBase::onTimeOut(const char* msgName) const
{
    ERR_LOG("System[%s] wait msg[%s] timeout!!!", getName(), msgName);
    throw("Fatal: receive msg timeout!");
}

void FakeSystemBase::onMsgSend(const char* msgName, const MsgId id) const
{
    INFO_LOG("System[%s] send msg[%s : %d]!", getName(), msgName, id);
}

void FakeSystemBase::onMsgRecv(const char* msgName, const MsgId id) const
{
    INFO_LOG("System[%s] recv msg[%s : %d]!", getName(), msgName, id);
}

void FakeSystemBase::send(const RawMsg& msg) const
{
    DatesSender::send(msg);
}

DATES_NS_END
