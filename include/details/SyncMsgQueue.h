#ifndef HE1281468_B42A_49BF_A7CE_BD21C0D881D7
#define HE1281468_B42A_49BF_A7CE_BD21C0D881D7

#include "details/MsgQueue.h"
#include <details/TaggedMsg.h>
#include <list>

DATES_NS_BEGIN

struct SyncMsgQueue : MsgQueue
{
    bool satisfy(const MsgMatcher&) const;
    ~SyncMsgQueue();

public:
    OVERRIDE(void insert(const TaggedMsg&));
    OVERRIDE(void insert(TaggedMsg&&));
    OVERRIDE(bool fetch(const MsgMatcher&, TaggedMsg&));
    OVERRIDE(void clear());
    OVERRIDE(bool isEmpty() const);

private:
    std::list<TaggedMsg> msgs;
};

DATES_NS_END

#endif
