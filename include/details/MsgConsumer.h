#ifndef H0DB3D3C8_B971_4B32_A1CA_5E763C531027
#define H0DB3D3C8_B971_4B32_A1CA_5E763C531027

#include "details/dates.h"
#include "base/Role.h"

DATES_NS_BEGIN

struct RawMsg;

DEFINE_ROLE(MsgConsumer)
{
    ABSTRACT(bool expected(const RawMsg&) const);
    ABSTRACT(void consume(const RawMsg&) const);
    ABSTRACT(void onError() const);
};

DATES_NS_END

#endif
