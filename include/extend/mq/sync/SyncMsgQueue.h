#ifndef HE1281468_B42A_49BF_A7CE_BD21C0D881D7
#define HE1281468_B42A_49BF_A7CE_BD21C0D881D7

#include <core/MsgQueue.h>
#include <core/RawMsg.h>
#include <list>

DATES_NS_BEGIN

struct SyncMsgQueue : MsgQueue
{
    bool satisfy(const MsgMatcher&) const;
    ~SyncMsgQueue();

public:
    OVERRIDE(void insert(const RawMsg&));
    OVERRIDE(void insert(RawMsg&&));
    OVERRIDE(bool fetch(const MsgMatcher&, RawMsg&));
    OVERRIDE(void clear());
    OVERRIDE(bool isEmpty() const);

private:
    std::list<RawMsg> msgs;
};

DATES_NS_END

#endif
