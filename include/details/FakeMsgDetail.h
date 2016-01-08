#ifndef H94482E7D_E520_4A89_8194_273CFF053FCF
#define H94482E7D_E520_4A89_8194_273CFF053FCF

#include "details/dates.h"
#include <string.h>

DATES_NS_BEGIN

template<typename MSG>
struct FakeMsgDetail : MSG
{
    FakeMsgDetail()
    {
        reset();
    }

    void reset() const
    {
        ::memset((void*)this, 0x0, sizeof(MSG));
    }
};

DATES_NS_END

#endif