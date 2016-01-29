#include "DatesFrame.h"
#include "base/Singleton.h"
#include "base/NullPtr.h"
#include "details/DatesReceiver.h"
#include "details/DatesSender.h"
#include "details/AsyncMsgQueue.h"
#include <thread>
#include <memory>

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
            msgQueue.reset(new SyncMsgQueue());
        }

        void asyncRun(const Sender& sender, const Receiver& receiver, const U32 waitTime)
        {
            this->sender = sender;
            this->receiver = receiver;

            if(__notnull__(t)) terminateThread();
            t = new std::thread([=]{this->receiver();});
            msgQueue.reset(new AsyncMsgQueue(waitTime));
        }

        void recv(const RawMsg& msg)
        {
            msgQueue->insert(msg);
        }

        void send(const RawMsg& msg)
        {
            sender(msg);
        }

        MsgQueue& getMsgQueue()
        {
            return *msgQueue;
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
        std::unique_ptr<MsgQueue> msgQueue;
    };
}

void DatesSender::send(const RawMsg& msg)
{
    DatesDetail::getInstance().send(msg);
}

void DatesReceiver::recv(const RawMsg& msg)
{
    DatesDetail::getInstance().recv(msg);
}

void DatesFrame::syncRun(const Sender& sender)
{
    DatesDetail::getInstance().syncRun(sender);
}

void DatesFrame::asyncRun(const Sender& sender, const Receiver& receiver, const U32 waitTime)
{
    DatesDetail::getInstance().asyncRun(sender, receiver, waitTime);
}

MsgQueue& DatesFrame::getMsgQueue()
{
    return DatesDetail::getInstance().getMsgQueue();
}

DATES_NS_END
