#include "AsyncSut.h"
#include "sut/Events.h"

SUT_NS_BEGIN

AsyncSut::AsyncSut()
: client(5001), t(new std::thread([this]{run();}))
{
}

AsyncSut::~AsyncSut()
{
    t->join();
}

void AsyncSut::run()
{
    U8 buffer[1024] = {0};

    while(true)
    {
        S32 r = client.receive(buffer, 1024);

        if(r <= 0) break;

        Status status = SutBase::receive(((Header*)buffer)->id, buffer, r);
        if(status != SUCCESS) break;
    }
}

void AsyncSut::doSend(const void* data, const U32 length)
{
    client.send("127.0.0.1", 5002, data, length);
}

SUT_NS_END
