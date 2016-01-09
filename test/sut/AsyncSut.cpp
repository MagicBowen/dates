#include "AsyncSut.h"
#include "sut/msgs.h"
#include "definition.h"

SUT_NS_BEGIN

AsyncSut::AsyncSut()
: client(SUT_ADDR, SUT_PORT), t(new std::thread([this]{run();}))
{
}

AsyncSut::~AsyncSut()
{
    t->join();
}

void AsyncSut::run()
{
    static U8 buffer[MAX_MSG_LENGTH] = {0};

    while(true)
    {
        S32 r = client.receive(buffer, MAX_MSG_LENGTH);

        if(r <= 0) break;

        Status status = SutBase::receive(((Header*)buffer)->id, buffer, r);
        if(status != SUCCESS) break;
    }
}

void AsyncSut::doSend(const void* data, const U32 length)
{
    client.send(DATES_ADDR, DATES_PORT, data, length);
}

SUT_NS_END
