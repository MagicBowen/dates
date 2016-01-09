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
    __def_fake_msg(EVENT_PING,      Ping);
    __def_fake_msg(EVENT_PONG,      Pong);
    __def_fake_msg(EVENT_TERMINATE, Terminate);

    __def_fake_sys_begin(Commander)
        __could_send(Ping);
        __could_recv(Pong);
        __could_send(Terminate);
        __could_recv(Terminate);
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
    FakeCommander commander;
    SyncSut sut;
};

TEST_F(SyncTest, should_receive_hello_from_sut_when_say_hello_to_sync_sut)
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

TEST_F(SyncTest, should_receive_pong_msg_when_send_ping_to_sync_sut)
{
    const U32 PAYLOAD = 1;

    commander.send([=](FAKE(Ping)& ping)
            {
                ping.request = PAYLOAD;
            });

    commander.recv([=](const FAKE(Pong)& pong)
            {
                ASSERT_EQ(PAYLOAD, pong.reply);
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
                        static U8 buffer[1024] = {0};
                        while(true)
                        {
                            S32 r = client.receive(buffer, 1024);
                            if(r <= 0) break;

                            EventId id = ((Header*)buffer)->id;
                            DatesReceiver::recv(id, *(new RawMsg((U32)r, buffer)));
                            if(EVENT_TERMINATE == id) return;
                        }
                    });
    }

protected:
    FakeCommander commander;
    const U32 PAYLOAD{1};

    // Normally, the ASYNC_SUT should be global,
    // and terminated once after all tests completed!
    UdpClient client{5002};
    AsyncSut sut;
};

TEST_F(AsyncTest, shoud_stop_dates_and_sut_when_send_terminate_msg)
{
    commander.send(DUMMY_SEND_MSG(Terminate));

    commander.recv(DUMMY_RECV_MSG(Terminate));
}

TEST_F(AsyncTest, should_receive_pong_msg_when_send_ping_to_async_sut)
{
    commander.send([this](FAKE(Ping)& ping)
            {
                ping.request = PAYLOAD;
            });

    commander.recv([this](const FAKE(Pong)& pong)
            {
                ASSERT_EQ(PAYLOAD, pong.reply);
            });

    commander.send(DUMMY_SEND_MSG(Terminate));

    commander.recv(DUMMY_RECV_MSG(Terminate));
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

