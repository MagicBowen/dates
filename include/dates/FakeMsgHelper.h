#ifndef H05B2224D_B926_4FC0_A936_67B52B8A98DE
#define H05B2224D_B926_4FC0_A936_67B52B8A98DE

#include <ccinfra/base/BaseTypes.h>
#include <dates/core/MsgId.h>
#include <dates/extend/fake/FakeMsg.h>
#include <dates/extend/fake/FakeName.h>

DATES_NS_BEGIN

////////////////////////////////////////////////////////
#define __def_fake_msg_begin(ID, MSG)       \
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

#define __def_fake_msg_end                  };

/////////////////////////////////////////////////////////
#define __def_fake_msg(ID, MSG)               \
__def_fake_msg_begin(ID, MSG)                 \
__def_fake_msg_end

/////////////////////////////////////////////////////////
#define DUMMY_SEND_MSG(NAME) [](FAKE(NAME)&){}
#define DUMMY_RECV_MSG(NAME) [](const FAKE(NAME)&){}

DATES_NS_END

#endif
