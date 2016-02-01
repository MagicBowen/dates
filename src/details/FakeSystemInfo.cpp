#include "details/FakeSystemInfo.h"

DATES_NS_BEGIN

FakeSystemInfo::FakeSystemInfo(const char* name)
: name(name)
{
}

const char* FakeSystemInfo::getName() const
{
    return name.c_str();
}

DATES_NS_END
