#ifndef H05B2224D_B926_4FC0_A936_67B52B8A98DE
#define H05B2224D_B926_4FC0_A936_67B52B8A98DE

#include "base/BaseTypes.h"
#include "FakeName.h"
#include "MsgId.h"
#include <string.h>

DATES_NS_BEGIN

///////////////////////////////////////////////////////
template<typename MSG>
struct FakeMsg : MSG
{
    FakeMsg()
    {
        reset();
    }

    void reset() const
    {
        ::memset((void*)this, 0x0, sizeof(MSG));
    }
};

////////////////////////////////////////////////////////
#define DEF_FAKE_MSG_BEGIN(ID, MSG)         \
struct FAKE(MSG) : FakeMsg<MSG>             \
{                                           \
    static const char* getName()            \
    {                                       \
        return #MSG;                        \
    }                                       \
    static MsgId getId()                    \
    {                                       \
        return ID;                          \
    }

#define DEF_FAKE_MSG_END                  };

/////////////////////////////////////////////////////////
#define DEF_FAKE_MSG(ID, MSG)               \
DEF_FAKE_MSG_BEGIN(ID, MSG)                 \
DEF_FAKE_MSG_END

DATES_NS_END

#endif
