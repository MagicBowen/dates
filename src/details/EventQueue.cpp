#include "details/EventQueue.h"
#include "details/EventConsumer.h"
#include "base/Event.h"
#include "base/Synchronization.h"
#include <condition_variable>
#include <iostream>
#include <sstream>
#include <chrono>
#include <map>

DATES_NS_BEGIN

namespace
{
    struct EventQueueImpl : EventQueue
    {
        ~EventQueueImpl()
        {
            for(auto event : events)
            {
                delete [] ((U8*)(event.second.getMsg()));
            }
        }

    private:
        OVERRIDE(void insert(const Event& event))
        {
            SYNCHRONIZED(mutex)
            {
                events.insert(std::make_pair(event.getEventId(), event));

                cond.notify_one();
            }
        }

        OVERRIDE(void consume(const EventConsumer& consumer))
        {
            SYNCHRONIZED(mutex)
            {
                cond.wait_for(LOCKER(mutex).getLocker(),
                              std::chrono::seconds(waitSeconds),
                              [&](){return find(consumer.getId());});

                if(!find(consumer.getId()))
                    return consumer.onTimeOut();

                return doConsume(consumer);
            }
        }

        OVERRIDE(void setWaitTime(const U32 seconds))
        {
            waitSeconds = seconds;
        }

    private:
        bool find(const EventId id) const
        {
            auto event = events.find(id);
            if(event == events.end()) return false;
            return true;
        }

        void doConsume(const EventConsumer& consumer)
        {
            auto event = events.find(consumer.getId());
            consumer.consume(event->second);

            events.erase(event);
            delete [] ((U8*)(event->second.getMsg()));
        }

    private:
        std::map<EventId, Event> events;
        std::condition_variable cond;
        std::mutex mutex;
        U32 waitSeconds{5};
    };
}

EventQueue& EventQueue::getInstance()
{
    static EventQueueImpl instance;
    return instance;
}

DATES_NS_END
