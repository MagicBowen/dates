#ifndef H1DC20EDF_DCB1_4EE0_A64C_3EE38DDB31DE
#define H1DC20EDF_DCB1_4EE0_A64C_3EE38DDB31DE

#include "sut_ns.h"
#include "EventId.h"

SUT_NS_BEGIN

struct OssSender
{
    static void send(const EventId, const void* data, const U32 length);
};

SUT_NS_END

#endif
