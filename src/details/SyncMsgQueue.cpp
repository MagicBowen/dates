#include "details/SyncMsgQueue.h"
#include "details/MsgConsumer.h"
#include "base/NullPtr.h"

DATES_NS_BEGIN

SyncMsgQueue::~SyncMsgQueue()
{
    clear();
}

bool SyncMsgQueue::satisfy(const MsgConsumer& consumer) const
{
    for(auto& msg : msgs)
    {
        if(consumer.expected(msg))  return true;
    }
    return false;
}

namespace
{
    template<typename Msgs>
    void doConsume( Msgs& msgs
                  , typename Msgs::iterator& msg
                  , const MsgConsumer& consumer)
    {
        consumer.consume(*msg);
        msgs.erase(msg);
        delete [] msg->getMsg();
    }
}

void SyncMsgQueue::consumedBy(const MsgConsumer& consumer)
{
    for(auto msg = msgs.begin(); msg != msgs.end(); ++msg)
    {
        if(consumer.expected(*msg))
        {
            return doConsume(msgs, msg, consumer);
        }
    }

    return consumer.onError();
}

void SyncMsgQueue::insert(const RawMsg& msg)
{
    msgs.push_back(msg);
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

DATES_NS_END
