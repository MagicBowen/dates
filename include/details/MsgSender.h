#ifndef H1DB8EC07_D721_4F43_BDAC_3313686E2B20
#define H1DB8EC07_D721_4F43_BDAC_3313686E2B20

#include "details/dates.h"
#include "base/Role.h"

DATES_NS_BEGIN

struct RawMsg;

DEFINE_ROLE(MsgSender)
{
    ABSTRACT(void sendMsg(const RawMsg&) const);
};

DATES_NS_END

#endif
