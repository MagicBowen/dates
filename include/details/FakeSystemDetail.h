#ifndef H3A33B15A_5386_4FF3_BB06_DA8484CB59C0
#define H3A33B15A_5386_4FF3_BB06_DA8484CB59C0

#include "details/FakeSystemBase.h"
#include "details/MsgQueue.h"
#include "details/MsgConsumer.h"
#include "details/RawMsg.h"
#include "details/MsgId.h"
#include "base/FunctionTraits.h"

DATES_NS_BEGIN

////////////////////////////////////////////////////////
template<typename FAKER>
struct FakeSystemDetail : private FakeSystemBase
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

DATES_NS_END

#endif
