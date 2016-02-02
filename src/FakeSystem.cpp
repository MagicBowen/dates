#include "FakeSystem.h"
#include "DatesUtils.h"
#include "details/FakeMsgListener.h"
#include "details/FakeMsgUtils.h"
#include "details/MsgSender.h"

DATES_NS_BEGIN

namespace
{
    struct FakeMsgSender : MsgSender
    {
    private:
        OVERRIDE(void send(const RawMsg& msg) const)
        {
            return DatesUtils::send(msg);
        }
    };

    struct FakeMsgUtilsImpl : FakeMsgUtils
    {
        FakeMsgUtilsImpl(const char* name)
        : listener(new FakeMsgListener(name))
        , sender(new FakeMsgSender())
        {
        }

    private:
        DECL_ROLE(MsgQueue)
        {
            return DatesUtils::getMsgQueue();
        }

        IMPL_ROLE_WITH_OBJ(MsgListener, *listener);
        IMPL_ROLE_WITH_OBJ(MsgSender,   *sender);

    private:
        std::unique_ptr<MsgListener> listener;
        std::unique_ptr<MsgSender> sender;
    };
}

FakeSystem::FakeSystem(const char* name)
: msgUtils(new FakeMsgUtilsImpl(name))
{
}

DATES_NS_END