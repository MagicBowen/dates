#ifndef HA8723E0D_CED2_473D_8680_81DA12BD5AF3
#define HA8723E0D_CED2_473D_8680_81DA12BD5AF3

#include "details/dates.h"
#include <functional>

DATES_NS_BEGIN

struct TaggedMsg;

using MsgMatcher = std::function<bool (const TaggedMsg&)>;

DATES_NS_END

#endif
