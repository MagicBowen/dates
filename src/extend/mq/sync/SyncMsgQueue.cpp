#include <dates/extend/mq/sync/SyncMsgQueue.h>

DATES_NS_BEGIN

bool SyncMsgQueue::satisfy(const MsgMatcher& matcher) const
{
    for(auto& msg : msgs)
    {
        if(matcher(msg))  return true;
    }
    return false;
}

void SyncMsgQueue::insert(const RawMsg& msg)
{
    msgs.push_back(msg);
}

void SyncMsgQueue::insert(RawMsg&& msg)
{
    msgs.push_back(std::move(msg));
}

bool SyncMsgQueue::fetch(const MsgMatcher& match, RawMsg& result)
{
    for(auto msg = msgs.begin(); msg != msgs.end(); ++msg)
    {
        if(match(*msg))
        {
            result = std::move(*msg);
            msgs.erase(msg);
            return true;;
        }
    }

    return false;
}

void SyncMsgQueue::clear()
{
     msgs.clear();
}

bool SyncMsgQueue::isEmpty() const
{
    return msgs.empty();
}

SyncMsgQueue::~SyncMsgQueue()
{
    clear();
}

DATES_NS_END
