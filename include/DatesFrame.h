#ifndef H6C9783B3_A46F_489B_9EE5_B208C5DCDBD2
#define H6C9783B3_A46F_489B_9EE5_B208C5DCDBD2

#include "details/MsgId.h"
#include <functional>

DATES_NS_BEGIN

struct RawMsg;

using Sender = std::function<void (const MsgId, const RawMsg&)>;
using Receiver = std::function<void ()>;

struct DatesFrame
{
    static void syncRun(const Sender&);
};

DATES_NS_END

#endif
