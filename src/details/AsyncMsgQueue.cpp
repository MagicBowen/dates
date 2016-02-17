#include "details/AsyncMsgQueue.h"
#include "base/Synchronization.h"
#include "base/NullPtr.h"

DATES_NS_BEGIN

AsyncMsgQueue::AsyncMsgQueue(const U32 waitSeconds)
: waitSeconds(waitSeconds)
{
}

void AsyncMsgQueue::insert(const TaggedMsg& msg)
{
    SYNCHRONIZED(mutex)
    {
        msgs.insert(msg);
        cond.notify_one();
    }
}

bool AsyncMsgQueue::fetch(const MsgMatcher& matcher, TaggedMsg& msg)
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
