#include <dates/factory/DatesAsyncFactory.h>
#include <dates/extend/runtime/async/AsyncDatesRuntime.h>

DATES_NS_BEGIN

DatesRuntime DatesAsyncFactory::createRuntime( const DatesSender& sender
                                             , const DatesReceiver& receiver
                                             , const U32 waitSeconds)
{
    auto runtime = new AsyncDatesRuntime(sender, waitSeconds);

    runtime->run(receiver);

    return DatesRuntime(runtime);
}

DATES_NS_END

