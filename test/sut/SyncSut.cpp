#include "sut/SyncSut.h"
#include "sut/msgs.h"
#include "details/RawMsg.h"
#include "details/DatesReceiver.h"
#include <string.h>

USING_DATES_NS

SUT_NS_BEGIN

void SyncSut::doSend(const void* data, const U32 length)
{
    auto msg = new U8[length];
    memcpy(msg, data, length);
    DatesReceiver::recv(RawMsg(((Header*)data)->id, msg, length));
}

SUT_NS_END
