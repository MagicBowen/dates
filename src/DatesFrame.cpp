#include "DatesFrame.h"
#include "base/log.h"
#include "MsgQueue.h"
#include <thread>
#include <memory>

DATES_NS_BEGIN

namespace
{
    struct DatesFrameImpl : DatesFrame
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
    private:
        OVERRIDE(void run( const Sender& sender
                         , Receiver* receiver))
        {
            this->sender = sender;
            this->receiver = receiver;

            if(__notnull__(receiver))
            {
                stop = false;
                t.reset(new std::thread([this]{while(!stop){(*(this->receiver))();}}));
            }
        }

        OVERRIDE(void recv(const MsgId id, const RawMsg& msg))
        {
            MsgQueue::getInstance().insert(id, msg);
        }

        OVERRIDE(void send(const MsgId id, const RawMsg& msg))
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

DatesFrame& DatesFrame::getInstance()
{
    static DatesFrameImpl instance;
    return instance;
}

DATES_NS_END
