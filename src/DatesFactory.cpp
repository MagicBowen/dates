#include "DatesFactory.h"
#include "details/SyncMsgQueue.h"
#include "details/AsyncMsgQueue.h"
#include "details/Runtime.h"
#include "details/MsgSender.h"
#include "details/MsgReceiver.h"
#include "base/NullPtr.h"
#include <thread>

DATES_NS_BEGIN

namespace
{
    ///////////////////////////////////////////////////////////
    template<typename MSG_QUEUE>
    struct GenericRuntime : Runtime
                          , private MsgSender
                          , private MsgReceiver
                          , protected MSG_QUEUE
    {
        template<typename... Paras>
        GenericRuntime(const DatesFactory::Sender& sender, Paras... paras)
        : sender(sender), MSG_QUEUE(paras...)
        {
        }

    private:
        OVERRIDE(void send(const RawMsg& msg))
        {
            sender(msg);
        }

        OVERRIDE(void recv(const RawMsg& msg))
        {
            return ROLE(MsgQueue).insert(msg);
        }

    private:
        DatesFactory::Sender sender;

    private:
        IMPL_ROLE(MsgSender);
        IMPL_ROLE(MsgReceiver);
        IMPL_ROLE(MsgQueue);
    };

    ///////////////////////////////////////////////////////////
    using SyncDatesRuntime = GenericRuntime<SyncMsgQueue>;

    ///////////////////////////////////////////////////////////
    struct AsyncDatesRuntime : GenericRuntime<AsyncMsgQueue>
    {
        AsyncDatesRuntime( const DatesFactory::Sender& sender
                         , const U32 waitSeconds)
        : GenericRuntime<AsyncMsgQueue>(sender, waitSeconds)
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
    auto runtime = new AsyncDatesRuntime(sender, waitSeconds);

    runtime->run(receiver);

    return DatesRuntime(runtime);
}

DATES_NS_END
