#ifndef H05B2224D_B926_4FC0_A936_67B52B8A98DD
#define H05B2224D_B926_4FC0_A936_67B52B8A98DD

#include "details/FakeSystemDetail.h"
#include <functional>

DATES_NS_BEGIN

///////////////////////////////////////////////////////////////
#define CHECKER_TYPE(MSG) std::function<void (const MSG&)>

#define COULD_RECV(MSG)                             \
void check(const CHECKER_TYPE(FAKE(MSG))& checker,  \
            const FAKE(MSG)& msg)                   \
{                                                   \
    checker(msg);                                   \
}

////////////////////////////////////////////////////////
#define BUILDER_TYPE(MSG) std::function<void (MSG&)>

#define COULD_SEND(MSG)                             \
void build(const BUILDER_TYPE(FAKE(MSG))& builder,  \
            FAKE(MSG)& msg)                         \
{                                                   \
    builder(msg);                                   \
}

////////////////////////////////////////////////////////
#define DEF_FAKE_SYSTEM_BEGIN(SYSTEM)               \
struct FAKE(SYSTEM) : FakeSystemDetail<FAKE(SYSTEM)>\
{                                                   \
private:                                            \
    OVERRIDE(const char* getName() const)           \
    {                                               \
        return #SYSTEM;                             \
    }                                               \
public:

#define DEF_FAKE_SYSTEM_END         };

DATES_NS_END

#endif
