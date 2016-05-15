#ifndef HDE682FC9_BB65_4707_BCBE_0BA478552648
#define HDE682FC9_BB65_4707_BCBE_0BA478552648

#include <dates/core/MsgTransit.h>
#include <dates/core/RawMsg.h>
#include <ccinfra/functional/FunctionTraits.h>

DATES_NS_BEGIN

DEFINE_ROLE(FakeSystemBase)
{
    template<typename CHECKER>
    void recv(const CHECKER& checker)
    {
        using MSG = ARG_TYPE(CHECKER);
        RawMsg msg = ROLE(MsgTransit).recvMsg(MSG::getName(), MSG::getId());
        checker(msg.castTo<MSG>());
    }

    template<typename BUILDER>
    void send(const BUILDER& builder)
    {
        using MSG = ARG_TYPE(BUILDER);
        RawMsg msg(MSG::getId(), sizeof(MSG));
        builder(msg.castTo<MSG>());
        ROLE(MsgTransit).sendMsg(MSG::getName(), msg);
    }

private:
    USE_ROLE(MsgTransit);
};

DATES_NS_END

#endif
