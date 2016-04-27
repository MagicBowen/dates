#ifndef H623AAACF_8BC4_4834_951A_0EEF3784CA62
#define H623AAACF_8BC4_4834_951A_0EEF3784CA62

#include <dates/extend/usings/DatesRuntime.h>
#include <dates/extend/usings/DatesSender.h>

DATES_NS_BEGIN

struct DatesSyncFactory
{
    static DatesRuntime createRuntime(const DatesSender&);
};

DATES_NS_END

#endif
