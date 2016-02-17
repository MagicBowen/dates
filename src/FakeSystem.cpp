#include "FakeSystem.h"
#include <DatesFactory.h>
#include "details/FakeMsgListener.h"
#include <details/FakeMsgTransit.h>
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

    struct FakeMsgTransitImpl : FakeMsgTransit
                              , private FakeMsgListener
                              , private FakeMsgSender
    {
        FakeMsgTransitImpl(const char* name, Runtime& runtime)
        : FakeMsgListener(name)
        , FakeMsgSender(runtime.ROLE(DatesSender))
        , runtime(runtime)
        {
        }

    private:
        IMPL_ROLE(MsgSender);
        IMPL_ROLE(MsgListener);
        IMPL_ROLE_WITH_OBJ(MsgQueue, runtime.ROLE(MsgQueue));

    private:
        Runtime& runtime;
    };
}

FakeSystem::FakeSystem(const char* name, Runtime& runtime)
: msgTransit(new FakeMsgTransitImpl(name, runtime))
{
}

DATES_NS_END
