#include "details/SyncMsgQueue.h"
#include "details/MsgConsumer.h"
#include "base/NullPtr.h"

DATES_NS_BEGIN

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
        if(consumer.expect(*msg))
        {
            return doConsume(msgs, msg, consumer);
        }
    }

    return consumer.onError();
}

bool SyncMsgQueue::satisfy(const MsgConsumer& consumer) const
{
    for(auto& msg : msgs)
    {
        if(consumer.expect(msg))  return true;
    }
    return false;
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

SyncMsgQueue::~SyncMsgQueue()
{
    clear();
}

DATES_NS_END
