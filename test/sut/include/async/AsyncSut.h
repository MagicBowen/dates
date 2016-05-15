#ifndef HB6741630_582C_4AD5_A920_47936480A5F4
#define HB6741630_582C_4AD5_A920_47936480A5F4

#include <common/sut.h>
#include <async/UdpClient.h>
#include <dates/core/MsgId.h>
#include <ccinfra/base/Status.h>
#include <thread>
#include <memory>

USING_DATES_NS
SUT_NS_BEGIN

struct AccessReq;
struct CfgRsp;

struct AsyncSut
{
    AsyncSut();
    ~AsyncSut();

private:
    void run();

private:
    Status receive(const MsgId, const void* data, const U32 length);
    void handle(const AccessReq&);
    void handle(const CfgRsp&);

private:
    void send(const MsgId, const void* data, const U32 length);
    void doSend(const void* data, const U32 length);

private:
    std::unique_ptr<std::thread> t;
    UdpClient client;
};

SUT_NS_END

#endif
