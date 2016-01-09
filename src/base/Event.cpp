#include "base/Event.h"
#include "base/NullPtr.h"

Event::Event() : eventId(0xFFFF), length(0), msg(__null_ptr__)
{
}

Event::Event(const EventId eventId, const U32 length, void* msg)
{
    update(eventId, length, msg);
}

void Event::update(const EventId eventId, const U32 length, void* msg)
{
    this->eventId = eventId;
    this->length = length;
    this->msg = msg;
}
