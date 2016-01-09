#include "DatesFrame.h"
#include "base/Singleton.h"
#include "base/NullPtr.h"
#include "details/DatesReceiver.h"
#include "details/DatesSender.h"
#include "details/MsgQueue.h"
#include <memory>
#include <thread>

DATES_NS_BEGIN

namespace
{
    DEF_SINGLETON(DatesDetail)
    {
        void run(const Sender& sender, const Receiver* receiver)
        {
            this->sender = sender;
            this->receiver = receiver;

            if(__notnull__(receiver))
            {
                t.reset(new std::thread([this]{while(true){(*(this->receiver))();}}));
            }
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
        Sender sender;
        const Receiver* receiver{__null_ptr__};
        std::unique_ptr<std::thread> t;
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
    DatesDetail::getInstance().run(sender, __null_ptr__);
}

void DatesFrame::asyncRun(const Sender& sender, const Receiver& receiver, const U32 waitTime)
{
    MsgQueue::getInstance().setWaitTime(waitTime);
    DatesDetail::getInstance().run(sender, &receiver);
}

DATES_NS_END

