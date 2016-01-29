#include "details/SyncMsgQueue.h"
#include "details/MsgConsumer.h"
#include "base/NullPtr.h"

DATES_NS_BEGIN

SyncMsgQueue::~SyncMsgQueue()
{
    clear();
}

const RawMsg* SyncMsgQueue::findBy(const MsgConsumer& consumer) const
{
    for(auto& msg : msgs)
    {
        if(consumer.isMatch(msg))  return &msg;
    }
    return __null_ptr__;
}

void SyncMsgQueue::consume(const MsgConsumer& consumer)
{
    auto msgIterator = msgs.begin();

    for(auto msgIterator = msgs.begin(); msgIterator != msgs.end(); ++msgIterator)
    {
        if(consumer.isMatch(*msgIterator))
        {
            msgs.erase(msgIterator);
            break;
        }
    }

    if(msgs.end() == msgIterator) return consumer.onError();

    consumer.consume(*msgIterator);
    delete [] msgIterator->getMsg();
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

DATES_NS_END
