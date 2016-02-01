#include "details/MsgActionListner.h"
#include "details/FakeSystemInfo.h"
#include "details/DatesSender.h"
#include "details/RawMsg.h"
#include "base/log.h"

DATES_NS_BEGIN

void MsgActionListner::onTimeOut(const char* msgName) const
{
    ERR_LOG("System[%s] wait msg[%s] timeout!!!", ROLE(FakeSystemInfo).getName(), msgName);
    throw("Fatal: receive msg timeout!");
}

void MsgActionListner::onMsgSend(const char* msgName, const MsgId id) const
{
    INFO_LOG("System[%s] send msg[%s : %d]!", ROLE(FakeSystemInfo).getName(), msgName, id);
}

void MsgActionListner::onMsgRecv(const char* msgName, const MsgId id) const
{
    INFO_LOG("System[%s] recv msg[%s : %d]!", ROLE(FakeSystemInfo).getName(), msgName, id);
}

void MsgActionListner::send(const RawMsg& msg) const
{
    DatesSender::send(msg);
}

DATES_NS_END
