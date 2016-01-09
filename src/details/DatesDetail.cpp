#include "DatesFrame.h"
#include "base/Singleton.h"
#include "base/NullPtr.h"
#include "details/DatesReceiver.h"
#include "details/DatesSender.h"
#include "details/EventQueue.h"
#include <thread>

DATES_NS_BEGIN

namespace
{
    DEF_SINGLETON(DatesDetail)
    {
        ~DatesDetail()
        {
            terminateThread();
        }

        void syncRun(const Sender& sender)
        {
            this->sender = sender;
        }

        void asyncRun(const Sender& sender, const Receiver& receiver)
        {
            this->sender = sender;
            this->receiver = receiver;

            if(__notnull__(t)) terminateThread();
            t = new std::thread([=]{this->receiver();});
        }

        void recv(const Event& event)
        {
            EventQueue::getInstance().insert(event);
        }

        void send(const Event& event)
        {
            sender(event);
        }

    private:
        void terminateThread()
        {
            t->join();
            delete t;
            t = __null_ptr__;
        }

    private:
        Sender sender;
        Receiver receiver;
        std::thread* t{__null_ptr__};
    };
}

void DatesSender::send(const Event& event)
{
    DatesDetail::getInstance().send(event);
}

void DatesReceiver::recv(const Event& event)
{
    DatesDetail::getInstance().recv(event);
}

void DatesFrame::syncRun(const Sender& sender)
{
    EventQueue::getInstance().setWaitTime(0);
    DatesDetail::getInstance().syncRun(sender);
}

void DatesFrame::asyncRun(const Sender& sender, const Receiver& receiver, const U32 waitTime)
{
    EventQueue::getInstance().setWaitTime(waitTime);
    DatesDetail::getInstance().asyncRun(sender, receiver);
}

DATES_NS_END
