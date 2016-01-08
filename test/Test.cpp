#include "gtest/gtest.h"
#include "sut/Events.h"
#include "FakeMsg.h"
#include "FakeSystem.h"
#include "DatesFrame.h"
#include "RawMsg.h"
#include "sut/Sut.h"
#include <string>

USING_DATES_NS
using namespace SUT;

namespace SUT
{
    void send(const MsgId id, const void* data, const U32 length)
    {
        DatesFrame::getInstance().recv(id, RawMsg(length, (U8*)data));
    }
}

namespace
{
    DEF_FAKE_MSG_BEGIN(EVENT_HELLO, Hello)
        void fill(const char* words)
        {
            strcpy(data, words);
        }

        const char* getWords() const
        {
            return data;
        }
    DEF_FAKE_MSG_END

    DEF_FAKE_MSG(EVENT_PING, Ping);
    DEF_FAKE_MSG(EVENT_PONG,   Pong);

    DEF_FAKE_SYSTEM_BEGIN(Neighbor)
        COULD_SEND(Hello);
        COULD_RECV(Hello);
    DEF_FAKE_SYSTEM_END

    DEF_FAKE_SYSTEM_BEGIN(Commander)
        COULD_SEND(Ping);
        COULD_RECV(Pong);
    DEF_FAKE_SYSTEM_END

}

struct DatesTest : public testing::Test
{
    void SetUp()
    {
        DatesFrame::getInstance().run(
                    [](const MsgId id, const RawMsg& msg)
                    {
                        Sut::receive(id, msg.getData(), msg.getLength());
                    });
    }

protected:
    FakeNeighbor neighbor;
    FakeCommander commander;
};

TEST_F(DatesTest, should_receive_hello_from_sut_when_say_hello_to_sut)
{
    neighbor.send([](FAKE(Hello)& hello)
            {
                hello.fill("Hi");
            });

    neighbor.recv([](const FAKE(Hello)& hello)
            {
                ASSERT_TRUE(strcmp("Who are you?", hello.getWords()) == 0);
            });
}

TEST_F(DatesTest, should_receive_resply_msg_when_send_request_to_sut)
{
    commander.send([](FAKE(Ping)& ping)
            {
                ping.request = 1;
            });

    commander.recv([](const FAKE(Pong)& pong)
            {
                ASSERT_EQ(1, pong.reply);
            });
}


int main(int argc, char* argv[])
{
    try
    {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    catch(std::exception& e)
    {
        std::cout << "FATAL: exception occur, [" << e.what() << "]!" << std::endl;
        return -1;
    }
}

