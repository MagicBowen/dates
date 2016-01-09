#ifndef H9CF1C00E_1374_476C_BB5B_09E7F032BE49
#define H9CF1C00E_1374_476C_BB5B_09E7F032BE49

#include "EventId.h"

struct Event
{
    Event();
    Event(const EventId eventId, const U32 length, void* msg);

    void update(const EventId eventId, const U32 length, void* msg);

    EventId getEventId() const
    {
        return eventId;
    }

    void* getMsg() const
    {
        return msg;
    }

    U32 getLength() const
    {
        return length;
    }

private:
    EventId    eventId;
    U32        length;
    void*      msg;
};

#endif
