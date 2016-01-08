#ifndef H1BE6A19E_9E50_4436_A8C8_A78E6EAFA10B
#define H1BE6A19E_9E50_4436_A8C8_A78E6EAFA10B

#include "EventId.h"
#include "base/Role.h"

SUT_NS_BEGIN

struct Hello;
struct Ping;

DEFINE_ROLE(SutBase)
{
    void receive(const EventId, const void* data, const U32 length);

private:
    void handleHello(const Hello&);
    void handlePing(const Ping&);

private:
    ABSTRACT(void send(const EventId, const void* data, const U32 length));
};


SUT_NS_END

#endif
