#include <dates/extend/fake/FakeMsgListener.h>
#include <ccinfra/log/log.h>

DATES_NS_BEGIN

FakeMsgListener::FakeMsgListener(const char* name) : sysName(name)
{
}

void FakeMsgListener::onMsgMiss(const char* msgName, const MsgId id) const
{
    ERR_LOG("System[%s] wait msg[%s : %d] failed!!!", sysName.c_str(), msgName, id);
    throw("Fatal: receive msg timeout!");
}

void FakeMsgListener::onMsgSend(const char* msgName, const MsgId id) const
{
    DBG_LOG("System[%s] send msg[%s : %d]!", sysName.c_str(), msgName, id);
}

void FakeMsgListener::onMsgRecv(const char* msgName, const MsgId id) const
{
    DBG_LOG("System[%s] recv msg[%s : %d]!", sysName.c_str(), msgName, id);
}

DATES_NS_END
