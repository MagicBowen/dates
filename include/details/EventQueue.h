#ifndef H26660305_7596_4C04_89EB_2384963F2EB5
#define H26660305_7596_4C04_89EB_2384963F2EB5

#include "details/dates.h"
#include "base/Role.h"
#include "base/BaseTypes.h"

struct Event;

DATES_NS_BEGIN

struct EventConsumer;

DEFINE_ROLE(EventQueue)
{
    static EventQueue& getInstance();

    ABSTRACT(void insert(const Event&));
    ABSTRACT(void consume(const EventConsumer&));
    ABSTRACT(void setWaitTime(const U32 seconds));
};

DATES_NS_END

#endif
