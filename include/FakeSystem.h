#ifndef H05CB1DAE_F659_4AB7_B2C1_E200271883CA
#define H05CB1DAE_F659_4AB7_B2C1_E200271883CA

#include "details/FakeSystemBase.h"
#include <memory>

DATES_NS_BEGIN

struct Runtime;

struct FakeSystem : FakeSystemBase
{
    FakeSystem(const char* name, Runtime&);

private:
    IMPL_ROLE_WITH_OBJ(MsgTransit, *msgTransit);

private:
    std::unique_ptr<MsgTransit> msgTransit;
};

DATES_NS_END

#endif
