#include <dates/factory/DatesSyncFactory.h>
#include <dates/extend/runtime/sync/SyncDatesRuntime.h>

DATES_NS_BEGIN

DatesRuntime DatesSyncFactory::createRuntime(const DatesSender& sender)
{
    return DatesRuntime(new SyncDatesRuntime(sender));
}

DATES_NS_END
