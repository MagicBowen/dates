#ifndef HE1281468_B42A_49BF_A7CE_BD21C0D881D7
#define HE1281468_B42A_49BF_A7CE_BD21C0D881D7

#include "details/MsgQueue.h"
#include "details/RawMsg.h"
#include <list>

DATES_NS_BEGIN

struct SyncMsgQueue : MsgQueue
{
    bool satisfy(const MsgConsumer&) const;
    ~SyncMsgQueue();

public:
    OVERRIDE(void insert(const RawMsg&));
    OVERRIDE(void consume(const MsgConsumer&));
    OVERRIDE(void clear());
    OVERRIDE(bool isEmpty() const);

private:
    std::list<RawMsg> msgs;
};

DATES_NS_END

#endif
