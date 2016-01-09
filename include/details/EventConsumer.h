#ifndef H1A930699_4C11_46B6_A574_31D7DB370F23
#define H1A930699_4C11_46B6_A574_31D7DB370F23

#include "details/dates.h"
#include "base/Role.h"
#include "base/EventId.h"

struct Event;

DATES_NS_BEGIN

DEFINE_ROLE(EventConsumer)
{
    ABSTRACT(EventId getId() const);
    ABSTRACT(void consume(const Event&) const);
    ABSTRACT(void onTimeOut() const);
};

DATES_NS_END

#endif
