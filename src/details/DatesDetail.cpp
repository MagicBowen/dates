#include "DatesFrame.h"
#include "details/DatesReceiver.h"
#include "details/DatesSender.h"
#include "details/MsgQueue.h"
#include <memory>
#include <thread>

DATES_NS_BEGIN

namespace
{
    struct DatesDetail
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

    DatesDetail dates;
}

void DatesSender::send(const MsgId id, const RawMsg& msg)
{
    dates.send(id, msg);
}

void DatesReceiver::recv(const MsgId id, const RawMsg& msg)
{
    dates.recv(id, msg);
}

void DatesFrame::run(const Sender& sender, Receiver* receiver)
{
    dates.run(sender, receiver);
}

DATES_NS_END

