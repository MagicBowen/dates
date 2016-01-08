#include "gtest/gtest.h"
#include "sut/Events.h"
#include "FakeMsg.h"
#include "FakeSystem.h"
#include "DatesFrame.h"
#include "sut/Sut.h"
#include <string>

USING_DATES_NS
USING_SUT_NS

/////////////////////////////////////////////////////////
namespace
{
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

    __def_fake_sys_begin(Neighbor)
        __could_send(Hello);
        __could_recv(Hello);
    __def_fake_sys_end

    /////////////////////////////////////////////////////
    __def_fake_msg(EVENT_PING,   Ping);
    __def_fake_msg(EVENT_PONG,   Pong);

    __def_fake_sys_begin(Commander)
        __could_send(Ping);
        __could_recv(Pong);
    __def_fake_sys_end

}

/////////////////////////////////////////////////////////
struct DatesTest : public testing::Test
{
    void SetUp()
    {
        DatesFrame::syncRun(
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
                hello.fill("Hey!");
            });

    neighbor.recv([](const FAKE(Hello)& hello)
            {
                ASSERT_TRUE(strcmp("Who are you?", hello.getWords()) == 0);
            });
}

TEST_F(DatesTest, should_receive_resply_msg_when_send_request_to_sut)
{
    const U32 PYLOAD = 1;

    commander.send([=](FAKE(Ping)& ping)
            {
                ping.request = PYLOAD;
            });

    commander.recv([=](const FAKE(Pong)& pong)
            {
                ASSERT_EQ(PYLOAD, pong.reply);
            });
}

/////////////////////////////////////////////////////////
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

