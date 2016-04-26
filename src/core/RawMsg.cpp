#include <core/RawMsg.h>
#include "base/NullPtr.h"
#include <string.h>

DATES_NS_BEGIN

RawMsg::RawMsg()
: id(0)
, length(0)
, data(__null_ptr__)
{
}

RawMsg::RawMsg(size_t length)
: id(0)
, length(length)
, data(new U8[length])
{
}

RawMsg::RawMsg(MsgId id, size_t length)
: RawMsg(length)
{
    this->id = id;
}

void RawMsg::copyFrom(const RawMsg& other)
{
    id = other.id;
    length = other.length;
    data = new U8[length];
    memcpy(data, other.data, other.length);
}

void RawMsg::copyFrom(RawMsg&& other)
{
    id = other.id;
    length = other.length;
    data = other.data;
    other.data = __null_ptr__;
}

RawMsg::RawMsg(const RawMsg& other)
{
    copyFrom(other);
}

RawMsg::RawMsg(RawMsg&& other)
{
    copyFrom(std::move(other));
}

RawMsg::~RawMsg()
{
    if(__notnull__(data))
    {
        delete [] data;
    }

    data = __null_ptr__;
}

DATES_NS_END
