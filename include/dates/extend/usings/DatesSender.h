#ifndef H2B2C3EE7_E987_409B_B828_823F4D5981A8
#define H2B2C3EE7_E987_409B_B828_823F4D5981A8

#include <dates/core/dates.h>
#include <functional>

DATES_NS_BEGIN

struct RawMsg;

using DatesSender = std::function<void (const RawMsg&)>;

DATES_NS_END

#endif
