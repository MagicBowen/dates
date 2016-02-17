#ifndef H8AFB07B2_FC75_4148_BE41_0DD0D8496FD2
#define H8AFB07B2_FC75_4148_BE41_0DD0D8496FD2

#include "details/MsgId.h"
#include "details/MsgCast.h"
#include <stddef.h>
#include <utility>

DATES_NS_BEGIN

struct RawMsg
{
    RawMsg();
    RawMsg(size_t length);
    RawMsg(MsgId id, size_t length);

    RawMsg(const RawMsg&);
    RawMsg(RawMsg&&);

    ~RawMsg();

    template<typename T>
    RawMsg& operator=(T&& rhs)
    {
        if(this != &rhs)
        {
            copyFrom(std::forward<T>(rhs));
        }

        return *this;
    }

    template<typename MSG>
    MSG& castTo() const
    {
        return msg_cast<MSG>(data);
    }

    void update(MsgId id, size_t length)
    {
        this->id = id;
        this->length = length;
    }

    MsgId getId() const
    {
        return id;
    }

    U8* getMsg() const
    {
        return data;
    }

    size_t getLength() const
    {
        return length;
    }

private:
    void copyFrom(const RawMsg&);
    void copyFrom(RawMsg&&);

private:
    MsgId id;
    size_t length;
    U8* data;
};

DATES_NS_END

#endif
