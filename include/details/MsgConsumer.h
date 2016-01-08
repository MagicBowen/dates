#ifndef H1A930699_4C11_46B6_A574_31D7DB370F23
#define H1A930699_4C11_46B6_A574_31D7DB370F23

#include "details/dates.h"
#include "details/MsgId.h"

DATES_NS_BEGIN

struct RawMsg;

DEFINE_ROLE(MsgConsumer)
{
    ABSTRACT(MsgId getMsgId() const);
    ABSTRACT(void consume(const RawMsg&) const);
    ABSTRACT(void onTimeOut() const);
};

DATES_NS_END

#endif
