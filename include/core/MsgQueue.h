#ifndef H8B4936B8_C0B2_4383_976B_302534D2E657
#define H8B4936B8_C0B2_4383_976B_302534D2E657

#include <core/MsgMatcher.h>
#include "base/Role.h"

DATES_NS_BEGIN

struct RawMsg;

DEFINE_ROLE(MsgQueue)
{
    ABSTRACT(void insert(const RawMsg&));
    ABSTRACT(void insert(RawMsg&&));
    ABSTRACT(bool fetch(const MsgMatcher&, RawMsg&));
    ABSTRACT(void clear());
    ABSTRACT(bool isEmpty() const);
};

DATES_NS_END

#endif
