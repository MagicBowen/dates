#ifndef HFC33001A_CA5F_442A_8E49_69371AAF3DF0
#define HFC33001A_CA5F_442A_8E49_69371AAF3DF0

#include "AsyncMsgs.h"

USING_SUT_NS

#include <msgcc/ErrorCodeInterpret.h>
#include "MsgMetas.h"

#include <msgcc/ConstrantInterpret.h>
#include "MsgMetas.h"

#include <msgcc/ConstructInterpret.h>
#include "MsgMetas.h"

#include <msgcc/Msgcc.h>

const U8 ERROR_OFFSET = 1;

__msgcc_implement(AccessReq, ERROR_OFFSET);
__msgcc_implement(AccessRsp, ERROR_OFFSET);

#endif
