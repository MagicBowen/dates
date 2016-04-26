#include <extend/runtime/async/AsyncDatesRuntime.h>
#include "base/NullPtr.h"

DATES_NS_BEGIN

AsyncDatesRuntime::AsyncDatesRuntime( const DatesSender& sender
                                    , const U32 waitSeconds)
: GenericRuntime<AsyncMsgQueue>(sender, waitSeconds)
, t(__null_ptr__)
{
}

void AsyncDatesRuntime::run(const DatesReceiver& receiver)
{
    if(__notnull__(t)) return;
    t = new std::thread(receiver);
}

AsyncDatesRuntime::~AsyncDatesRuntime()
{
    terminate();
}

void AsyncDatesRuntime::terminate()
{
    if(__notnull__(t))
    {
        t->join();
        delete t;
        t = __null_ptr__;
    }
}

DATES_NS_END
