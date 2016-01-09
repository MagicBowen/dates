#ifndef H18F78CFE_4245_4B74_A331_726361D95A6B
#define H18F78CFE_4245_4B74_A331_726361D95A6B

#include "details/dates.h"
#include "base/Role.h"
#include "base/BaseTypes.h"
#include "base/EventId.h"

struct Event;

DATES_NS_BEGIN

DEFINE_ROLE(FakeSystemBase)
{
    void onTimeOut(const char* msgName) const;
    void onMsgSend(const char* msgName, const EventId) const;
    void onMsgRecv(const char* msgname, const EventId) const;
    void send(const Event&) const;

private:
    ABSTRACT(const char* getName() const);
};

DATES_NS_END

#endif
