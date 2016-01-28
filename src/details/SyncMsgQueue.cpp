#include "details/SyncMsgQueue.h"
#include "details/MsgConsumer.h"
#include "base/NullPtr.h"

DATES_NS_BEGIN

RawMsg* SyncMsgQueue::findBy(const MsgConsumer& consumer) const
{
    for(auto& msg : msgs)
    {
        if(consumer.isMatch(msg))  return &msg;
    }
    return __null_ptr__;
}

void SyncMsgQueue::consume(const MsgConsumer& consumer)
{
    auto msg = findBy(consumer);

    if(__null(msg)) return consumer.onError();

    consumer.consume(*msg);
    msgs.remove(*msg);
}

void SyncMsgQueue::insert(RawMsg& msg)
{
    msgs.push_back(msg);
}

void SyncMsgQueue::clear()
{
    msgs.clear();
}

DATES_NS_END
