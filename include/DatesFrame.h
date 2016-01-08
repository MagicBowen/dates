#ifndef H6C9783B3_A46F_489B_9EE5_B208C5DCDBD2
#define H6C9783B3_A46F_489B_9EE5_B208C5DCDBD2

#include "base/Role.h"
#include "base/NullPtr.h"
#include "details/MsgId.h"
#include <functional>

DATES_NS_BEGIN

struct RawMsg;

DEFINE_ROLE(DatesFrame)
{
    static DatesFrame& getInstance();

    using Sender = std::function<void (const MsgId, const RawMsg&)>;
    using Receiver = std::function<void ()>;

    ABSTRACT(void run(const Sender&, Receiver* receiver = __null_ptr__));
    ABSTRACT(void recv(const MsgId, const RawMsg&));
    ABSTRACT(void send(const MsgId, const RawMsg&));
};

DATES_NS_END

#endif
