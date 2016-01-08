#ifndef H26660305_7596_4C04_89EB_2384963F2EB5
#define H26660305_7596_4C04_89EB_2384963F2EB5

#include "base/Role.h"
#include "details/MsgId.h"

DATES_NS_BEGIN

struct RawMsg;
struct MsgConsumer;

DEFINE_ROLE(MsgQueue)
{
    static MsgQueue& getInstance();

    ABSTRACT(void insert(const MsgId, const RawMsg&));
    ABSTRACT(void consume(const MsgConsumer&));
    ABSTRACT(void setWaitTime(const U32 seconds));
};

DATES_NS_END

#endif
