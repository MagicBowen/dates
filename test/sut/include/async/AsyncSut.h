#ifndef HB6741630_582C_4AD5_A920_47936480A5F4
#define HB6741630_582C_4AD5_A920_47936480A5F4

#include <common/SutBase.h>
#include <async/UdpClient.h>
#include <thread>
#include <memory>

SUT_NS_BEGIN

struct AsyncSut : SutBase
{
    AsyncSut();
    ~AsyncSut();

private:
    void run();

private:
    OVERRIDE(void doSend(const void* data, const U32 length));

private:
    std::unique_ptr<std::thread> t;
    UdpClient client;
};

SUT_NS_END

#endif
