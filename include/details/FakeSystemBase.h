#ifndef HDE682FC9_BB65_4707_BCBE_0BA478552648
#define HDE682FC9_BB65_4707_BCBE_0BA478552648

#include "details/MsgUtils.h"
#include "details/RawMsg.h"
#include "base/FunctionTraits.h"
#include <functional>
#include <memory>

DATES_NS_BEGIN

DEFINE_ROLE(FakeSystemBase)
{
    template<typename CHECKER>
    void recv(const CHECKER& checker)
    {
        using MSG = ARG_TYPE(CHECKER);
        RawMsg& msg = ROLE(MsgUtils).recvMsg(MSG::getName(), MSG::getId());
        checker(msg.castTo<MSG>());
        delete [] msg.getMsg();
    }

    template<typename BUILDER>
    void send(const BUILDER& builder)
    {
        using MSG = ARG_TYPE(BUILDER);
        std::unique_ptr<MSG> msg(new MSG());
        builder(*msg);
        ROLE(MsgUtils).sendMsg(MSG::getName(), RawMsg(MSG::getId(), (U8*)(msg.get()), sizeof(MSG)));
    }

private:
    USE_ROLE(MsgUtils);
};

DATES_NS_END

#endif
