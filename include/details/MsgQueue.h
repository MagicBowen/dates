#ifndef H8B4936B8_C0B2_4383_976B_302534D2E657
#define H8B4936B8_C0B2_4383_976B_302534D2E657

#include "details/dates.h"
#include "base/Role.h"

DATES_NS_BEGIN

struct RawMsg;
struct MsgConsumer;

DEFINE_ROLE(MsgQueue)
{
    ABSTRACT(void insert(const RawMsg&));
    ABSTRACT(void consumedBy(const MsgConsumer&));
    ABSTRACT(void clear());
    ABSTRACT(bool isEmpty() const);
};

DATES_NS_END

#endif
