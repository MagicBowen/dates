#ifndef HFC6F0342_70AE_4849_BB06_D96BCD68B052
#define HFC6F0342_70AE_4849_BB06_D96BCD68B052

#include <dates/core/MsgListener.h>
#include <string>

DATES_NS_BEGIN

struct FakeMsgListener : MsgListener
{
    FakeMsgListener(const char* name);

private:
    OVERRIDE(void onMsgMiss(const char* msgName, const MsgId) const);
    OVERRIDE(void onMsgSend(const char* msgName, const MsgId) const);
    OVERRIDE(void onMsgRecv(const char* msgname, const MsgId) const);

private:
    std::string sysName;
};

DATES_NS_END

#endif
