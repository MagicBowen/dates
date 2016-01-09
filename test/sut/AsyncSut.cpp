#include "AsyncSut.h"
#include "sut/Events.h"

SUT_NS_BEGIN

AsyncSut::AsyncSut()
: client(5001), t([this]{run();})
{
}

void AsyncSut::run()
{
    static U8 buffer[1024] = {0};

    while(true)
    {
        S16 r = client.receive(buffer, 1024);
        if(r > 0)
        {
            SutBase::receive(((Header*)buffer)->id, buffer, r);
        }
    }
}

void AsyncSut::send(const EventId, const void* data, const U32 length)
{
    client.send("127.0.0.1", 5002, data, length);
}

SUT_NS_END
