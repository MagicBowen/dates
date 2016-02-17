#ifndef H6C9783B3_A46F_489B_9EE5_B208C5DCDBD2
#define H6C9783B3_A46F_489B_9EE5_B208C5DCDBD2

#include "base/BaseTypes.h"
#include "DatesRuntime.h"
#include <functional>

DATES_NS_BEGIN

struct RawMsg;

struct DatesFactory
{
    using Sender = std::function<void (const RawMsg&)>;
    using Receiver = std::function<void ()>;

    static DatesRuntime createSyncRuntime(const Sender&);

    static DatesRuntime createAsyncRuntime( const Sender&
                                          , const Receiver&
                                          , const U32 waitSeconds = DEFAULT_WAIT_SECONDS);

private:
    static const U32 DEFAULT_WAIT_SECONDS = 5;
};

DATES_NS_END

#endif
