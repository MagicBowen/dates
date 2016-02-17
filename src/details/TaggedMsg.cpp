#include <details/TaggedMsg.h>
#include "base/NullPtr.h"

DATES_NS_BEGIN

TaggedMsg::TaggedMsg()
: msg(__null_ptr__), length(0), id()
{
}

TaggedMsg::TaggedMsg(MsgId id, U8* msg, U32 length)
: id(id), msg(msg), length(length)
{
}

void TaggedMsg::update(MsgId id, U8* msg, U32 length)
{
    this->id = id;
    this->msg = msg;
    this->length = length;
}

MsgId TaggedMsg::getId() const
{
    return id;
}

U8* TaggedMsg::getMsg() const
{
    return msg;
}

U32 TaggedMsg::getLength() const
{
    return length;
}

DATES_NS_END
