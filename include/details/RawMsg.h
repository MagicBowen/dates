#ifndef H4E17EE64_DFD7_4626_8E68_BFEE787FF603
#define H4E17EE64_DFD7_4626_8E68_BFEE787FF603

#include "details/dates.h"
#include "details/MsgId.h"

DATES_NS_BEGIN

struct RawMsg
{
    RawMsg(MsgId id, U8* msg, U32 length)
    : id(id), msg(msg), length(length)
    {
    }

    MsgId getId() const
    {
        return id;
    }

    U8* getMsg() const
    {
        return msg;
    }

    U32 getLength() const
    {
        return length;
    }

private:
    U8*   msg;
    U32   length;
    MsgId id;
};

DATES_NS_END

#endif
