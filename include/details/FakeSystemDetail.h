#ifndef H3A33B15A_5386_4FF3_BB06_DA8484CB59C0
#define H3A33B15A_5386_4FF3_BB06_DA8484CB59C0

#include "details/MsgActionListner.h"
#include "details/MsgConsumer.h"
#include "details/RawMsg.h"
#include "details/MsgSender.h"
#include "base/FunctionTraits.h"
#include "details/MsgQueue.h"
#include "base/Role.h"

DATES_NS_BEGIN

////////////////////////////////////////////////////////
template<typename FAKER>
struct FakeSystemDetail : private MsgActionListner
{
    template<typename CHECKER>
    void recv(const CHECKER& checker)
    {
        typedef ARG_TYPE(CHECKER) Msg;

        struct Consumer: MsgConsumer
        {
            Consumer(const char* msgName,
                     const MsgId id,
                     FAKER& sys,
                     const CHECKER& checker)
            : msgName(msgName)
            , id(id)
            , sys(sys)
            , checker(checker)
            {}

        private:
            OVERRIDE(bool expect(const RawMsg& rawMsg) const)
            {
                return id == rawMsg.getId();
            }

            OVERRIDE(void consume(const RawMsg& rawMsg) const)
            {
                auto msg = *reinterpret_cast<const Msg*>(rawMsg.getMsg());
                sys.check(checker, msg);
            }
            OVERRIDE(void onError() const)
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

        ROLE(MsgQueue).consumedBy(consumer);
        MsgActionListner::onMsgRecv(Msg::getName(), Msg::getId());
    }

    template<typename BUILDER>
    void send(const BUILDER& builder)
    {
        typedef ARG_TYPE(BUILDER) Msg;

        Msg msg;
        static_cast<FAKER&>(*this).build(builder, msg);

        MsgActionListner::onMsgSend(Msg::getName(), Msg::getId());
        ROLE(MsgSender).sendMsg(RawMsg(Msg::getId(), (U8*)(&msg), sizeof(Msg)));
    }

private:
    USE_ROLE(MsgQueue);
    USE_ROLE(MsgSender);
};

DATES_NS_END

#endif
