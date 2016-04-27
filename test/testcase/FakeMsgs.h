#ifndef H6ADB511A_4C29_47C9_B3D0_D7AEB51C8752
#define H6ADB511A_4C29_47C9_B3D0_D7AEB51C8752

#include <dates/FakeMsg.h>
#include <sut/include/common/Msgs.h>
#include <string.h>

USING_DATES_NS
USING_SUT_NS

__def_fake_msg_begin(EVENT_HELLO, Hello)
    void fill(const char* words)
    {
        strcpy(data, words);
    }

    const char* getWords() const
    {
        return data;
    }
__def_fake_msg_end

__def_fake_msg(EVENT_PING,      Ping);
__def_fake_msg(EVENT_PONG,      Pong);
__def_fake_msg(EVENT_TERMINATE, Terminate);

#endif
