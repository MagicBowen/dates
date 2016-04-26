#include <sync/SyncSut.h>
#include <common/Msgs.h>
#include "core/RawMsg.h"
#include "core/MsgQueue.h"
#include <string.h>

SUT_NS_BEGIN

SyncSut::SyncSut(MsgQueue& msgQueue)
: msgQueue(msgQueue)
{
}

void SyncSut::doSend(const void* data, const U32 length)
{
    RawMsg msg(((Header*)data)->id, length);
    memcpy(msg.getMsg(), data, length);
    msgQueue.insert(std::move(msg));
}

SUT_NS_END
