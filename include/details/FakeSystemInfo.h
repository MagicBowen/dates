#ifndef H50EE5712_492C_486D_A372_4F09C90826EC
#define H50EE5712_492C_486D_A372_4F09C90826EC

#include "details/dates.h"
#include "base/Role.h"
#include <string>

DATES_NS_BEGIN

struct FakeSystemInfo
{
    FakeSystemInfo(const char* name);
    const char* getName() const;

private:
    std::string name;
};

DATES_NS_END

#endif
