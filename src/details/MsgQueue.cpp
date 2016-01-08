#include "details/MsgQueue.h"
#include "details/RawMsg.h"
#include "details/MsgConsumer.h"
#include "base/Synchronization.h"
#include <map>
#include <condition_variable>
#include <chrono>
#include <sstream>
#include <iostream>

DATES_NS_BEGIN

namespace
{
    struct MsgQueueImpl : MsgQueue
    {
        ~MsgQueueImpl()
        {
            for(auto msg : msgs)
            {
                delete msg.second;
            }
        }

    private:
        OVERRIDE(void insert(const MsgId id, const RawMsg& msg))
        {
            SYNCHRONIZED(mutex)
            {
                msgs.insert(std::make_pair(id, &msg));

                cond.notify_one();
            }
        }

        OVERRIDE(void consume(const MsgConsumer& consumer))
        {
            SYNCHRONIZED(mutex)
            {
                cond.wait_for(LOCKER(mutex).getLocker(),
                              std::chrono::seconds(WAIT_SECONDS),
                              [&](){return find(consumer.getMsgId());});

                if(!find(consumer.getMsgId()))
                    return consumer.onTimeOut();

                return doConsume(consumer);
            }
        }

    private:
        bool find(const MsgId id) const
        {
            auto msg = msgs.find(id);
            if(msg == msgs.end()) return false;
            return true;
        }

        void doConsume(const MsgConsumer& consumer)
        {
            auto msg = msgs.find(consumer.getMsgId());
            consumer.consume(*(msg->second));

            msgs.erase(msg);
        }

    private:
        enum
        {
            WAIT_SECONDS = 5
        };

    private:
        std::map<MsgId, const RawMsg*> msgs;
        std::condition_variable cond;
        std::mutex mutex;
    };
}

MsgQueue& MsgQueue::getInstance()
{
    static MsgQueueImpl instance;
    return instance;
}

DATES_NS_END
