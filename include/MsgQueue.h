#ifndef H26660305_7596_4C04_89EB_2384963F2EB5
#define H26660305_7596_4C04_89EB_2384963F2EB5

#include "base/Role.h"
#include "base/dates.h"
#include "MsgId.h"

DATES_NS_BEGIN

struct RawMsg;
struct MsgConsumer;

DEFINE_ROLE(MsgQueue)
{
    static MsgQueue& getInstance();

    ABSTRACT(void insert(const MsgId, const RawMsg&));
    ABSTRACT(void consume(const MsgConsumer&));
};

DATES_NS_END

#endif
