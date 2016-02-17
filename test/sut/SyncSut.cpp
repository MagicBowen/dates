#include "sut/SyncSut.h"
#include "sut/msgs.h"
#include "details/TaggedMsg.h"
#include "details/MsgQueue.h"
#include <string.h>

SUT_NS_BEGIN

SyncSut::SyncSut(MsgQueue& msgQueue)
: msgQueue(msgQueue)
{
}

void SyncSut::doSend(const void* data, const U32 length)
{
    TaggedMsg msg(((Header*)data)->id, length);
    memcpy(msg.getMsg(), data, length);
    msgQueue.insert(std::move(msg));
}

SUT_NS_END
