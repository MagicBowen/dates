#ifndef HDC088B47_6642_44DC_9C7F_82CAF7DDA4D2
#define HDC088B47_6642_44DC_9C7F_82CAF7DDA4D2

#include "base/BaseTypes.h"
#include <extend/usings/DatesRuntime.h>
#include <extend/usings/DatesSender.h>
#include <extend/usings/DatesReceiver.h>

DATES_NS_BEGIN

struct DatesAsyncFactory
{
    static DatesRuntime createRuntime( const DatesSender&
                                     , const DatesReceiver&
                                     , const U32 waitSeconds = DEFAULT_WAIT_SECONDS);

private:
    static const U32 DEFAULT_WAIT_SECONDS = 5;
};

DATES_NS_END

#endif
