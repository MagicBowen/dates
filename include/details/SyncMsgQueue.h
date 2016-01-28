#ifndef HE1281468_B42A_49BF_A7CE_BD21C0D881D7
#define HE1281468_B42A_49BF_A7CE_BD21C0D881D7

#include "details/MsgQueue.h"
#include <list>

DATES_NS_BEGIN

struct SyncMsgQueue : MsgQueue
{
    RawMsg* findBy(const MsgConsumer&) const;

public:
    OVERRIDE(void insert(RawMsg&));
    OVERRIDE(void consume(const MsgConsumer&));
    OVERRIDE(void clear());

private:
    std::list<RawMsg> msgs;
};

DATES_NS_END

#endif
