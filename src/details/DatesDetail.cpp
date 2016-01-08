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
    //        OVERRIDE(~DatesFrameImpl())
    //        {
    //            if(__notnull__(receiver))
    //            {
    //                stop = true; // Exist danger!!!
    //                t->join();
    //            }
    //        }
    //
        void run(const Sender& sender, Receiver* receiver)
        {
            this->sender = sender;
            this->receiver = receiver;

            if(__notnull__(receiver))
            {
                stop = false;
                t.reset(new std::thread([this]{while(!stop){(*(this->receiver))();}}));
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
        Receiver* receiver{__null_ptr__};
        std::unique_ptr<std::thread> t;
        bool stop{true};
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

DATES_NS_END

