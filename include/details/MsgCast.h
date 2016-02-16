#ifndef H71DFD35D_D425_4B39_B0EC_2AB44ADCE4EA
#define H71DFD35D_D425_4B39_B0EC_2AB44ADCE4EA

#include "details/dates.h"

DATES_NS_BEGIN

template<typename MSG>
const MSG& msg_cast(const void *data)
{
    return *(reinterpret_cast<const MSG*>(data));
}

DATES_NS_END

#endif
