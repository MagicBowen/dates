#ifndef H3A33B15A_5386_4FF3_BB06_DA8484CB59C0
#define H3A33B15A_5386_4FF3_BB06_DA8484CB59C0

#include "details/FakeSystemBase.h"
#include "details/EventQueue.h"
#include "details/EventConsumer.h"
#include "base/FunctionTraits.h"
#include "base/Event.h"

DATES_NS_BEGIN

////////////////////////////////////////////////////////
template<typename FAKER>
struct FakeSystemDetail : private FakeSystemBase
{
    template<typename CHECKER>
    void recv(const CHECKER& checker)
    {
        typedef ARG_TYPE(CHECKER) Msg;

        struct Consumer: EventConsumer
        {
            Consumer(const char* msgName,
                     const EventId id,
                     FAKER& sys,
                     const CHECKER& checker)
            : msgName(msgName)
            , id(id)
            , sys(sys)
            , checker(checker)
            {}

        private:
            OVERRIDE(EventId getId() const)
            {
                return id;
            }
            OVERRIDE(void consume(const Event& event) const)
            {
                auto msg = *reinterpret_cast<const Msg*>(event.getMsg());
                sys.check(checker, msg);
            }
            OVERRIDE(void onTimeOut() const)
            {
                sys.onTimeOut(msgName);
            }

        private:
            const char* msgName;
            const EventId id;
            FAKER& sys;
            const CHECKER& checker;
        };

        Consumer consumer(Msg::getName(),
                          Msg::getId(),
                          static_cast<FAKER&>(*this),
                          checker);

        EventQueue::getInstance().consume(consumer);
        FakeSystemBase::onMsgRecv(Msg::getName(), Msg::getId());
    }

    template<typename BUILDER>
    void send(const BUILDER& builder)
    {
        typedef ARG_TYPE(BUILDER) Msg;

        Msg msg;
        static_cast<FAKER&>(*this).build(builder, msg);

        FakeSystemBase::onMsgSend(Msg::getName(), Msg::getId());
        FakeSystemBase::send(Event(Msg::getId(), sizeof(Msg), &msg));
    }
};

DATES_NS_END

#endif
