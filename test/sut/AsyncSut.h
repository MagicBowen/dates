#ifndef HB6741630_582C_4AD5_A920_47936480A5F4
#define HB6741630_582C_4AD5_A920_47936480A5F4

#include "sut/SutBase.h"

SUT_NS_BEGIN

struct AsyncSut : SutBase
{
    AsyncSut();
    ~AsyncSut();

private:
    OVERRIDE(void send(const EventId, const void* data, const U32 length));

private:
    int sockfd;
};

SUT_NS_END

#endif
