#include "details/RawMsg.h"
#include "base/NullPtr.h"

DATES_NS_BEGIN

RawMsg::RawMsg()
: msg(__null_ptr__), length(0), id()
{
}

RawMsg::RawMsg(MsgId id, U8* msg, U32 length)
: id(id), msg(msg), length(length)
{
}

void RawMsg::update(MsgId id, U8* msg, U32 length)
{
    this->id = id;
    this->msg = msg;
    this->length = length;
}

MsgId RawMsg::getId() const
{
    return id;
}

U8* RawMsg::getMsg() const
{
    return msg;
}

U32 RawMsg::getLength() const
{
    return length;
}

DATES_NS_END
