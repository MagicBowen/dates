#ifndef HD824EACF_A83D_4B03_BBD3_13589EAA8A81
#define HD824EACF_A83D_4B03_BBD3_13589EAA8A81

#include <dates/core/Runtime.h>
#include <dates/core/MsgSender.h>
#include <dates/extend/usings/DatesSender.h>

DATES_NS_BEGIN

template<typename MSG_QUEUE>
struct GenericRuntime : Runtime
                      , private MsgSender
                      , protected MSG_QUEUE
{
    template<typename... Paras>
    GenericRuntime(const DatesSender& sender, Paras... paras)
    : sender(sender), MSG_QUEUE(paras...)
    {
    }

private:
    OVERRIDE(void send(const RawMsg& msg))
    {
        sender(msg);
    }

private:
    DatesSender sender;

private:
    IMPL_ROLE(MsgSender);
    IMPL_ROLE(MsgQueue);
};

DATES_NS_END

#endif
