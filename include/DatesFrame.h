#ifndef H6C9783B3_A46F_489B_9EE5_B208C5DCDBD2
#define H6C9783B3_A46F_489B_9EE5_B208C5DCDBD2

#include "details/dates.h"
#include "base/BaseTypes.h"
#include <functional>

DATES_NS_BEGIN

struct MsgQueue;
struct RawMsg;

using Sender = std::function<void (const RawMsg&)>;
using Receiver = std::function<void ()>;

struct DatesFrame
{
    static void syncRun(const Sender&);
    static void asyncRun(const Sender&, const Receiver&, const U32 waitTime = 5);
    static MsgQueue& getMsgQueue();
};

DATES_NS_END

#endif
