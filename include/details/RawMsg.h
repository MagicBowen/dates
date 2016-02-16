#ifndef H4E17EE64_DFD7_4626_8E68_BFEE787FF603
#define H4E17EE64_DFD7_4626_8E68_BFEE787FF603

#include "details/MsgId.h"
#include "details/MsgCast.h"
#include "base/NullPtr.h"

DATES_NS_BEGIN

struct RawMsg
{
    RawMsg();
    RawMsg(MsgId, U8* msg, U32 length);

    void update(MsgId, U8* msg, U32 length);

    MsgId getId() const;
    U32 getLength() const;
    U8* getMsg() const;

    template<typename MSG>
    const MSG& castTo() const
    {
        return msg_cast<MSG>(msg);
    }

private:
    U8*   msg;
    U32   length;
    MsgId id;
};

DATES_NS_END

#endif
