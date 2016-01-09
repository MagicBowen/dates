#include "sut/SyncSut.h"
#include "sut/Events.h"
#include "details/RawMsg.h"
#include "details/DatesReceiver.h"

USING_DATES_NS

SUT_NS_BEGIN

void SyncSut::doSend(const void* data, const U32 length)
{
    DatesReceiver::recv(((Header*)data)->id, *(new RawMsg(length, (U8*)data)));
}

SUT_NS_END
