#include "details/SyncMsgQueue.h"

DATES_NS_BEGIN

bool SyncMsgQueue::satisfy(const MsgMatcher& matcher) const
{
    for(auto& msg : msgs)
    {
        if(matcher(msg))  return true;
    }
    return false;
}

void SyncMsgQueue::insert(const TaggedMsg& msg)
{
    msgs.push_back(msg);
}

bool SyncMsgQueue::fetch(const MsgMatcher& match, TaggedMsg& result)
{
    for(auto msg = msgs.begin(); msg != msgs.end(); ++msg)
    {
        if(match(*msg))
        {
            result.update(msg->getId(), msg->getMsg(), msg->getLength());
            msgs.erase(msg);
            return true;;
        }
    }

    return false;
}

void SyncMsgQueue::clear()
{
    for(auto msg : msgs)
    {
        delete [] msg.getMsg();
    }

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
