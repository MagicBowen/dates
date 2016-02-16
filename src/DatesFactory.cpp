#include "DatesFactory.h"
#include "details/SyncMsgQueue.h"
#include "details/AsyncMsgQueue.h"
#include "details/Runtime.h"
#include "details/DatesSender.h"
#include "details/DatesReceiver.h"
#include "base/NullPtr.h"
#include <thread>

DATES_NS_BEGIN

namespace
{
    ///////////////////////////////////////////////////////////
    struct DatesSenderImpl : DatesSender
    {
        DatesSenderImpl(const DatesFactory::Sender& sender)
        : sender(sender)
        {
        }

    private:
        OVERRIDE(void send(const RawMsg& msg))
        {
            sender(msg);
        }

    private:
        DatesFactory::Sender sender;
    };

    ///////////////////////////////////////////////////////////
    struct DatesReceiverImpl : DatesReceiver
    {
    private:
        OVERRIDE(void recv(const RawMsg& msg))
        {
            return ROLE(MsgQueue).insert(msg);
        }

    private:
        USE_ROLE(MsgQueue);
    };

    ///////////////////////////////////////////////////////////
    struct SyncDatesRuntime : Runtime
                            , private DatesSenderImpl
                            , private DatesReceiverImpl
                            , private SyncMsgQueue

    {
        SyncDatesRuntime(const DatesFactory::Sender& sender)
        : DatesSenderImpl(sender)
        {
        }

    private:
        IMPL_ROLE(DatesSender);
        IMPL_ROLE(DatesReceiver);
        IMPL_ROLE(MsgQueue);
    };

    ///////////////////////////////////////////////////////////
    struct AsyncDatesRuntime : Runtime
                             , private DatesSenderImpl
                             , private DatesReceiverImpl
                             , private AsyncMsgQueue
    {
        AsyncDatesRuntime(const DatesFactory::Sender& sender, const U32 waitSeconds)
        : DatesSenderImpl(sender), AsyncMsgQueue(waitSeconds)
        {
        }

        void run(const DatesFactory::Receiver& receiver)
        {
            if(__notnull__(t)) return;
            t = new std::thread(receiver);
        }

        ~AsyncDatesRuntime()
        {
            terminateThread();
        }

    private:
        void terminateThread()
        {
            if(__notnull__(t))
            {
                t->join();
                delete t;
                t = __null_ptr__;
            }
        }

    private:
        IMPL_ROLE(DatesSender);
        IMPL_ROLE(DatesReceiver);
        IMPL_ROLE(MsgQueue);

    private:
        std::thread* t{__null_ptr__};
    };
}

///////////////////////////////////////////////////////////
DatesRuntime DatesFactory::createSyncRuntime(const Sender& sender)
{
    return DatesRuntime(new SyncDatesRuntime(sender));
}

///////////////////////////////////////////////////////////
DatesRuntime DatesFactory::createAsyncRuntime( const Sender& sender
                                             , const Receiver& receiver
                                             , const U32 waitSeconds)
{
    auto dates = new AsyncDatesRuntime(sender, waitSeconds);
    dates->run(receiver);

    return DatesRuntime(dates);
}


DATES_NS_END
