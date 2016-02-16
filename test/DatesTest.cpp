#include "gtest/gtest.h"
#include "sut/msgs.h"
#include "FakeMsg.h"
#include "FakeSystem.h"
#include <DatesFactory.h>
#include "sut/SyncSut.h"
#include "sut/AsyncSut.h"
#include "details/MsgId.h"
#include "details/RawMsg.h"
#include <details/Runtime.h>
#include "details/DatesReceiver.h"
#include "definition.h"
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

    __def_fake_msg(EVENT_PING,      Ping);
    __def_fake_msg(EVENT_PONG,      Pong);
    __def_fake_msg(EVENT_TERMINATE, Terminate);

}

/////////////////////////////////////////////////////////
struct SyncTest : public testing::Test
{
    SyncTest()
    : runtime(DatesFactory::createSyncRuntime([this](const RawMsg& msg){syncSend(msg);}))
    , neighbor("neighbor", *runtime)
    , commander("commander", *runtime)
    , sut(runtime->ROLE(DatesReceiver))
    {
    }

private:
    void syncSend(const RawMsg& msg)
    {
        sut.receive(msg.getId(), msg.getMsg(), msg.getLength());
    }

protected:
    DatesRuntime runtime;
    FakeSystem neighbor;
    FakeSystem commander;
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


///////////////////////////////////////////////////////
struct AsyncTest : public testing::Test
{
    AsyncTest()
    : runtime(DatesFactory::createAsyncRuntime([this](const RawMsg& msg){asyncSend(msg);},
                                      [this](){asyncRecv();}))
    , commander("commander", *runtime)
    {
    }

private:
    void asyncSend(const RawMsg& msg)
    {
        U8* data = static_cast<U8*>(msg.getMsg());
        ((Header*)data)->id = msg.getId();
        client.send(SUT_ADDR, SUT_PORT, data, msg.getLength());
    }

    void asyncRecv()
    {
        while(true)
        {
            auto msg = new U8[MAX_MSG_LENGTH];

            S32 r = client.receive(msg, MAX_MSG_LENGTH);
            if(r <= 0) break;

            MsgId id = ((Header*)msg)->id;
            runtime->ROLE(DatesReceiver).recv(RawMsg(id, msg, (U32)r));
            if(EVENT_TERMINATE == id) return;
        }
    }

protected:
    // XXX: the udp client should be initialed before dates frame;
    // bcz the dates run receiving thread which using the udp client!
    UdpClient client{DATES_ADDR, DATES_PORT};
    AsyncSut sut;

    DatesRuntime runtime;
    FakeSystem commander;
    const U32 PAYLOAD{1};
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

