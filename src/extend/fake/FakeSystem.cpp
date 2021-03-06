#include <dates/extend/fake/FakeSystem.h>
#include <dates/extend/fake/FakeMsgListener.h>
#include <dates/extend/fake/FakeMsgTransit.h>
#include <dates/core/MsgSender.h>
#include <dates/core/Runtime.h>

DATES_NS_BEGIN

namespace
{
    struct FakeMsgTransitImpl : FakeMsgTransit
                              , private FakeMsgListener
    {
        FakeMsgTransitImpl(const char* name, Runtime& runtime)
        : FakeMsgListener(name)
        , runtime(runtime)
        {
        }

    private:
        IMPL_ROLE(MsgListener);
        IMPL_ROLE_WITH_OBJ(MsgSender, runtime.ROLE(MsgSender));
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
