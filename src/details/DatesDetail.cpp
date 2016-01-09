#include "DatesFrame.h"
#include "base/Singleton.h"
#include "base/NullPtr.h"
#include "details/DatesReceiver.h"
#include "details/DatesSender.h"
#include "details/MsgQueue.h"
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

        void recv(const MsgId id, const RawMsg& msg)
        {
            MsgQueue::getInstance().insert(id, msg);
        }

        void send(const MsgId id, const RawMsg& msg)
        {
            sender(id, msg);
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

void DatesSender::send(const MsgId id, const RawMsg& msg)
{
    DatesDetail::getInstance().send(id, msg);
}

void DatesReceiver::recv(const MsgId id, const RawMsg& msg)
{
    DatesDetail::getInstance().recv(id, msg);
}

void DatesFrame::syncRun(const Sender& sender)
{
    MsgQueue::getInstance().setWaitTime(0);
    DatesDetail::getInstance().syncRun(sender);
}

void DatesFrame::asyncRun(const Sender& sender, const Receiver& receiver, const U32 waitTime)
{
    MsgQueue::getInstance().setWaitTime(waitTime);
    DatesDetail::getInstance().asyncRun(sender, receiver);
}

DATES_NS_END
