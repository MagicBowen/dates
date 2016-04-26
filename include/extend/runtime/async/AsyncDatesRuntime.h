#ifndef H01DEE9D9_8187_41AB_A7FA_41AD72416AD2
#define H01DEE9D9_8187_41AB_A7FA_41AD72416AD2

#include <extend/mq/async/AsyncMsgQueue.h>
#include <extend/runtime/GenericRuntime.h>
#include <extend/usings/DatesSender.h>
#include <extend/usings/DatesReceiver.h>
#include <thread>

DATES_NS_BEGIN

struct AsyncDatesRuntime : GenericRuntime<AsyncMsgQueue>
{
    AsyncDatesRuntime(const DatesSender&, const U32 waitSeconds);
    void run(const DatesReceiver&);
    ~AsyncDatesRuntime();

private:
    void terminate();

private:
    std::thread* t;
};

DATES_NS_END

#endif
