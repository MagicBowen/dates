#ifndef H2DB038A9_C644_42DD_B30E_DA4E2EFE463A
#define H2DB038A9_C644_42DD_B30E_DA4E2EFE463A

#include "base/BaseTypes.h"
#include "details/dates.h"

DATES_NS_BEGIN

struct RawMsg
{
    RawMsg(const U32 length, const U8* msg);

    U32 getLength() const;
    const U8* getData() const;

private:
    enum
    {
        MAX_MSG_LENGTH = 8192
    };

    U32 length;
    U8  data[MAX_MSG_LENGTH];
};

DATES_NS_END

#endif
