#ifndef HE88AAE58_7D7F_4533_9909_AF9C0360C0AC
#define HE88AAE58_7D7F_4533_9909_AF9C0360C0AC

#include <common/sut.h>
#include <dates/base/BaseTypes.h>
#include <dates/base/MsgId.h>

USING_DATES_NS
SUT_NS_BEGIN

const MsgId EVENT_ACCESS_REQ = 0;
const MsgId EVENT_ACCESS_RSP = 1;
const MsgId EVENT_SUB_CFG = 2;
const MsgId EVENT_SUB_RSP = 3;

struct Header
{
    MsgId id;
};

struct AccessReq
{
    Header header;
    U32 capability;
};

struct AccessRsp
{
    Header header;
    U32 result;
};

struct CfgReq
{
    Header header;
    U32 capability;
};

struct CfgRsp
{
    Header header;
    U32 result;
};

SUT_NS_END

#endif
