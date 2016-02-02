#ifndef H05CB1DAE_F659_4AB7_B2C1_E200271883CA
#define H05CB1DAE_F659_4AB7_B2C1_E200271883CA

#include "details/FakeSystemBase.h"

DATES_NS_BEGIN

struct DatesFrame;

struct FakeSystem : FakeSystemBase
{
    FakeSystem(const char* name, DatesFrame&);

private:
    IMPL_ROLE_WITH_OBJ(MsgUtils, *msgUtils);

private:
    std::unique_ptr<MsgUtils> msgUtils;
};

DATES_NS_END

#endif
