#include "sut/SyncSut.h"
#include "sut/msgs.h"
#include "details/RawMsg.h"
#include "details/DatesReceiver.h"
#include <string.h>

SUT_NS_BEGIN

SyncSut::SyncSut(DatesReceiver& receiver)
: receiver(receiver)
{
}

void SyncSut::doSend(const void* data, const U32 length)
{
    auto msg = new U8[length];
    memcpy(msg, data, length);
    receiver.recv(RawMsg(((Header*)data)->id, msg, length));
}

SUT_NS_END
