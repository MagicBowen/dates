#ifndef H8B4936B8_C0B2_4383_976B_302534D2E657
#define H8B4936B8_C0B2_4383_976B_302534D2E657

#include "details/MsgMatcher.h"
#include "base/Role.h"

DATES_NS_BEGIN

struct TaggedMsg;

DEFINE_ROLE(MsgQueue)
{
    ABSTRACT(void insert(const TaggedMsg&));
    ABSTRACT(void insert(TaggedMsg&&));
    ABSTRACT(bool fetch(const MsgMatcher&, TaggedMsg&));
    ABSTRACT(void clear());
    ABSTRACT(bool isEmpty() const);
};

DATES_NS_END

#endif
