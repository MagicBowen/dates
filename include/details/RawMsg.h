#ifndef H4E17EE64_DFD7_4626_8E68_BFEE787FF603
#define H4E17EE64_DFD7_4626_8E68_BFEE787FF603

#include "details/dates.h"
#include "base/BaseTypes.h"

DATES_NS_BEGIN

struct RawMsg
{
    RawMsg(void* msg, U32 length)
    : msg(msg), length(length)
    {
    }

    void* getMsg()
    {
        return msg;
    }

    U32 getlength() const
    {
        return length;
    }

private:
    void* msg;
    U32   length;
};

DATES_NS_END

#endif
