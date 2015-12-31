#ifndef H05B2224D_B926_4FC0_A936_67B52B8A98DD
#define H05B2224D_B926_4FC0_A936_67B52B8A98DD

#include "FakeSystemBase.h"
#include "FakeName.h"
#include <MsgQueue.h>
#include "base/FunctionTraits.h"
#include "MsgConsumer.h"
#include "FakeSystem.h"
#include "RawMsg.h"
#include "MsgId.h"
#include <functional>
#include <string>

DATES_NS_BEGIN

////////////////////////////////////////////////////////
template<typename FAKER>
struct FakeSystem : private FakeSystemBase
{
    template<typename CHECKER>
    void recv(const CHECKER& checker)
    {
        typedef ARG_TYPE(CHECKER) Msg;

        struct Consumer: MsgConsumer
        {
            Consumer(const char* msgName,
                     const MsgId id, FAKER& sys,
                     const CHECKER& checker)
            : msgName(msgName)
            , id(id)
            , sys(sys)
            , checker(checker)
            {}

        private:
            OVERRIDE(MsgId getMsgId() const)
            {
                return id;
            }
            OVERRIDE(void consume(const RawMsg& msg) const)
            {
                auto event = *reinterpret_cast<const Msg*>(msg.getData());
                sys.check(checker, event);
            }
            OVERRIDE(void onTimeOut() const)
            {
                sys.onTimeOut(msgName);
            }

        private:
            const char* msgName;
            const MsgId id;
            FAKER& sys;
            const CHECKER& checker;
        };

        Consumer consumer(Msg::getName(),
                          Msg::getId(),
                          static_cast<FAKER&>(*this),
                          checker);

        FakeSystemBase::onMsgRecv(Msg::getName(), Msg::getId());
        MsgQueue::getInstance().consume(consumer);
    }

    template<typename BUILDER>
    void send(const BUILDER& builder)
    {
        typedef ARG_TYPE(BUILDER) Msg;

        Msg msg;
        static_cast<FAKER&>(*this).build(builder, msg);

        FakeSystemBase::send(Msg::getId(), sizeof(Msg), &msg);
        FakeSystemBase::onMsgSend(Msg::getName(), Msg::getId());
    }
};

///////////////////////////////////////////////////////////////
#define CHECKER_TYPE(MSG) std::function<void (const MSG&)>

#define COULD_RECV(MSG)                             \
void check(const CHECKER_TYPE(FAKE(MSG))& checker,  \
            const FAKE(MSG)& msg)                   \
{                                                   \
    checker(msg);                                   \
}

////////////////////////////////////////////////////////
#define BUILDER_TYPE(MSG) std::function<void (MSG&)>

#define COULD_SEND(MSG)                             \
void build(const BUILDER_TYPE(FAKE(MSG))& builder,  \
            FAKE(MSG)& msg)                         \
{                                                   \
    builder(msg);                                   \
}

////////////////////////////////////////////////////////
#define DEF_FAKE_SYSTEM_BEGIN(SYSTEM)               \
struct FAKE(SYSTEM) : FakeSystem<FAKE(SYSTEM)>      \
{                                                   \
private:                                            \
    OVERRIDE(const char* getName() const)           \
    {                                               \
        return #SYSTEM;                             \
    }                                               \
public:

#define DEF_FAKE_SYSTEM_END         };

DATES_NS_END

#endif
