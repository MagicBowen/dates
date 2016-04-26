#include <extend/mq/async/AsyncMsgQueue.h>
#include "base/Synchronization.h"
#include "base/NullPtr.h"

DATES_NS_BEGIN

AsyncMsgQueue::AsyncMsgQueue(const U32 waitSeconds)
: waitSeconds(waitSeconds)
{
}

template<typename T> void AsyncMsgQueue::doInsert(T&& msg)
{
    SYNCHRONIZED(mutex)
    {
        msgs.insert(std::forward<T>(msg));
        cond.notify_one();
    }
}

void AsyncMsgQueue::insert(const RawMsg& msg)
{
    doInsert(msg);
}

void AsyncMsgQueue::insert(RawMsg&& msg)
{
    doInsert(std::move(msg));
}

bool AsyncMsgQueue::fetch(const MsgMatcher& matcher, RawMsg& msg)
{
    SYNCHRONIZED(mutex)
    {
        bool result = cond.wait_for(LOCKER(mutex).getLocker(),
                      std::chrono::seconds(waitSeconds),
                      [&](){return msgs.satisfy(matcher);});

        return msgs.fetch(matcher, msg);
    }

    return false;
}

void AsyncMsgQueue::clear()
{
    SYNCHRONIZED(mutex)
    {
        msgs.clear();
    }
}

bool AsyncMsgQueue::isEmpty() const
{
    return msgs.isEmpty();
}

DATES_NS_END
