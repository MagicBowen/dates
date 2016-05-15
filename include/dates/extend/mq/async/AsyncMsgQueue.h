#ifndef H13237791_6170_4524_8B9E_5D304D7EAA2A
#define H13237791_6170_4524_8B9E_5D304D7EAA2A

#include <ccinfra/base/BaseTypes.h>
#include <dates/extend/mq/sync/SyncMsgQueue.h>
#include <condition_variable>
#include <mutex>

DATES_NS_BEGIN

struct AsyncMsgQueue : MsgQueue
{
    AsyncMsgQueue(const U32 waitSeconds);

private:
    OVERRIDE(void insert(const RawMsg&));
    OVERRIDE(void insert(RawMsg&&));
    OVERRIDE(bool fetch(const MsgMatcher&, RawMsg&));
    OVERRIDE(void clear());
    OVERRIDE(bool isEmpty() const);

private:
    template<typename T> void doInsert(T&&);

private:
    SyncMsgQueue msgs;
    std::condition_variable cond;
    std::mutex mutex;
    U32 waitSeconds;
};

DATES_NS_END

#endif
