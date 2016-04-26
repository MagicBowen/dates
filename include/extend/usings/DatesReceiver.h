#ifndef H1AE39370_6AF0_4C89_95A6_0D6401AB2E57
#define H1AE39370_6AF0_4C89_95A6_0D6401AB2E57

#include "core/dates.h"
#include <functional>

DATES_NS_BEGIN

struct RawMsg;

using DatesReceiver = std::function<void ()>;

DATES_NS_END

#endif
