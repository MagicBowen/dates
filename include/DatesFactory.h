#ifndef H6C9783B3_A46F_489B_9EE5_B208C5DCDBD2
#define H6C9783B3_A46F_489B_9EE5_B208C5DCDBD2

#include "details/dates.h"
#include "base/BaseTypes.h"
#include <functional>
#include <memory>

DATES_NS_BEGIN

struct RawMsg;
struct DatesFrame;

struct DatesFactory
{
    using Sender = std::function<void (const RawMsg&)>;
    using Receiver = std::function<void ()>;
    using DatesFramePtr = std::unique_ptr<DatesFrame>;

    enum{ DEFAULT_WAIT_SECONDS = 5 };

    static DatesFramePtr createSyncFrame(const Sender&);
    static DatesFramePtr createAsyncFrame(const Sender&, const Receiver&,
                                          const U32 waitSeconds = DEFAULT_WAIT_SECONDS);
};

DATES_NS_END

#endif
