#include "FakeSystem.h"
#include "DatesFrame.h"
#include "details/FakeMsgListener.h"
#include "details/FakeMsgUtils.h"
#include "details/MsgSender.h"
#include "details/DatesSender.h"

DATES_NS_BEGIN

namespace
{
    struct FakeMsgSender : MsgSender
    {
    private:
        OVERRIDE(void send(const RawMsg& msg) const)
        {
            return DatesSender::send(msg);
        }
    };

    struct FakeMsgUtilsImpl : FakeMsgUtils
    {
        FakeMsgUtilsImpl(const char* name)
        : queue(DatesFrame::getMsgQueue())
        , listener(new FakeMsgListener(name))
        , sender(new FakeMsgSender())
        {
        }

    private:
        IMPL_ROLE_WITH_OBJ(MsgQueue,    queue);
        IMPL_ROLE_WITH_OBJ(MsgListener, *listener);
        IMPL_ROLE_WITH_OBJ(MsgSender,   *sender);

    private:
        MsgQueue& queue;
        std::unique_ptr<MsgListener> listener;
        std::unique_ptr<MsgSender> sender;
    };
}

FakeSystem::FakeSystem(const char* name)
: msgUtils(new FakeMsgUtilsImpl(name))
{
}

DATES_NS_END
