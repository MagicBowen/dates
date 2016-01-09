#ifndef H6C9783B3_A46F_489B_9EE5_B208C5DCDBD2
#define H6C9783B3_A46F_489B_9EE5_B208C5DCDBD2

#include "details/dates.h"
#include "base/EventId.h"
#include <functional>

struct Event;

DATES_NS_BEGIN

using Sender = std::function<void (const Event&)>;
using Receiver = std::function<void ()>;

struct DatesFrame
{
    static void syncRun(const Sender&);
    static void asyncRun(const Sender&, const Receiver&, const U32 waitTime = 5);
};

DATES_NS_END

#endif
