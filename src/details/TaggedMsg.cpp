#include <details/TaggedMsg.h>
#include "base/NullPtr.h"
#include <string.h>

DATES_NS_BEGIN

TaggedMsg::TaggedMsg()
: id(0)
, length(0)
, data(__null_ptr__)
{
}

TaggedMsg::TaggedMsg(size_t length)
: id(0)
, length(length)
, data(new U8[length])
{

}

TaggedMsg::TaggedMsg(MsgId id, size_t length)
: TaggedMsg(length)
{
    this->id = id;
}

void TaggedMsg::copyFrom(const TaggedMsg& other)
{
    id = other.id;
    length = other.length;
    data = new U8[length];
    memcpy(data, other.data, other.length);
}

void TaggedMsg::copyFrom(TaggedMsg&& other)
{
    id = other.id;
    length = other.length;
    data = other.data;
    other.data = __null_ptr__;
}

TaggedMsg::TaggedMsg(const TaggedMsg& other)
{
    copyFrom(other);
}

TaggedMsg::TaggedMsg(TaggedMsg&& other)
{
    copyFrom(std::move(other));
}

TaggedMsg::~TaggedMsg()
{
    if(__notnull__(data))
    {
        delete [] data;
    }

    data = __null_ptr__;
}

DATES_NS_END
