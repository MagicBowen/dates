#include "gtest/gtest.h"
#include "sut/Events.h"
#include "FakeMsg.h"
#include "FakeSystem.h"
#include "DatesFrame.h"
#include "sut/SyncSut.h"
#include "sut/AsyncSut.h"
#include "details/DatesReceiver.h"
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
struct SyncTest : public testing::Test
{
    void SetUp()
    {
        DatesFrame::syncRun(
                    [this](const MsgId id, const RawMsg& msg)
                    {
                        sut.receive(id, msg.getData(), msg.getLength());
                    });
    }

protected:
    FakeNeighbor neighbor;
    SyncSut sut;
};

TEST_F(SyncTest, should_sync_receive_hello_from_sut_when_say_hello_to_sync_sut)
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

/////////////////////////////////////////////////////////
struct AsyncTest : public testing::Test
{
    void SetUp()
    {
        DatesFrame::asyncRun(
                    [this](const MsgId id, const RawMsg& msg)
                    {
                        U8* data = const_cast<U8*>(msg.getData());
                        ((Header*)data)->id = id;
                        client.send("127.0.0.1", 5001, data, msg.getLength());
                    },
                    [this]()
                    {
                        while(true)
                        {
                            U8 buffer[1024] = {0};
                            S16 r = client.receive(buffer, 1024);
                            if(r > 0)
                            {
                                DatesReceiver::recv(((Header*)buffer)->id, RawMsg((U32)r, buffer));
                            }
                        }
                    });
    }

protected:
    FakeCommander commander;
    AsyncSut sut;
    const U32 PAYLOAD{1};
    UdpClient client{5002};
};

TEST_F(AsyncTest, should_async_receive_pong_msg_when_send_ping_to_async_sut)
{
    commander.send([this](FAKE(Ping)& ping)
            {
                ping.request = PAYLOAD;
            });

    commander.recv([this](const FAKE(Pong)& pong)
            {
                ASSERT_EQ(PAYLOAD, pong.reply);
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

