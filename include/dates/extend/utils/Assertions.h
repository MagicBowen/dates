#ifndef HF1B8C242_CB17_4359_AF75_90DC1827BD35
#define HF1B8C242_CB17_4359_AF75_90DC1827BD35

#include <dates/core/dates.h>
#include <ccinfra/log/log.h>
#include <ccinfra/base/Status.h>

DATES_NS_BEGIN

#define INVOKE_FAILURE(log)  throw(log)

#define DATES_ASSERT(expression, log)       \
if((expression) != SUCCESS)                 \
{                                           \
    FATAL_LOG(log);                         \
    INVOKE_FAILURE(log);                    \
}

DATES_NS_END

#endif
