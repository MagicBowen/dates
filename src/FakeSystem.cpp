#include "FakeSystem.h"
#include <DatesFactory.h>
#include "details/FakeMsgListener.h"
#include "details/FakeMsgUtils.h"
#include "details/MsgSender.h"
#include <details/Runtime.h>
#include "details/DatesSender.h"

DATES_NS_BEGIN

namespace
{
    struct FakeMsgSender : MsgSender
    {
        FakeMsgSender(DatesSender& sender)
        : sender(sender)
        {
        }

    private:
        OVERRIDE(void send(const RawMsg& msg) const)
        {
            return sender.send(msg);
        }

    private:
        DatesSender& sender;
    };

    struct FakeMsgUtilsImpl : FakeMsgUtils
    {
        FakeMsgUtilsImpl(const char* name, Runtime& frame)
        : queue(frame.ROLE(MsgQueue))
        , listener(new FakeMsgListener(name))
        , sender(new FakeMsgSender(frame.ROLE(DatesSender)))
        {
        }

    private:
        IMPL_ROLE_WITH_OBJ(MsgQueue, queue);
        IMPL_ROLE_WITH_OBJ(MsgListener, *listener);
        IMPL_ROLE_WITH_OBJ(MsgSender,   *sender);

    private:
        MsgQueue& queue;
        std::unique_ptr<MsgListener> listener;
        std::unique_ptr<MsgSender> sender;
    };
}

FakeSystem::FakeSystem(const char* name, Runtime& frame)
: msgUtils(new FakeMsgUtilsImpl(name, frame))
{
}

DATES_NS_END
