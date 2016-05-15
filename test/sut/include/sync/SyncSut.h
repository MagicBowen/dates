#ifndef H454A7D46_0360_4776_A923_E98CF3108421
#define H454A7D46_0360_4776_A923_E98CF3108421

#include <common/sut.h>
#include <dates/core/dates.h>
#include <dates/core/MsgId.h>
#include <ccinfra/base/Status.h>

USING_DATES_NS
DATES_FWD_DECL(MsgQueue);

SUT_NS_BEGIN

struct Hello;
struct Ping;
struct Terminate;

struct SyncSut
{
    SyncSut(MsgQueue&);
    Status receive(const MsgId, const void* data, const U32 length);

private:
    void handleHello(const Hello&);
    void handlePing(const Ping&);
    void handleTerminate(const Terminate&);

private:
    void send(const MsgId, const void* data, const U32 length);
    void doSend(const void* data, const U32 length);

private:
    MsgQueue& msgQueue;
};

SUT_NS_END

#endif
