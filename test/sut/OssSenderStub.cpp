#include "OssSender.h"
#include "details/RawMsg.h"
#include "details/DatesReceiver.h"

USING_DATES_NS

SUT_NS_BEGIN

void OssSender::send(const EventId id, const void* data, const U32 length)
{
    DatesReceiver::recv(id, RawMsg(length, (U8*)data));
}

SUT_NS_END

