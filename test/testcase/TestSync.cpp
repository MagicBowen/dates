#include "gtest/gtest.h"
#include "dates/core/Runtime.h"
#include "dates/factory/DatesSyncFactory.h"
#include "dates/FakeSystem.h"
#include "sut/include/common/config.h"
#include "sut/include/sync/SyncSut.h"
#include "FakeMsgs.h"

/////////////////////////////////////////////////////////////////////
struct SyncTest : public testing::Test
{
    SyncTest()
    : runtime(DatesSyncFactory::createRuntime([this](const RawMsg& msg){syncSend(msg);}))
    , neighbor("neighbor", *runtime)
    , commander("commander", *runtime)
    , sut(runtime->ROLE(MsgQueue))
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

TEST_F(SyncTest, shoud_receive_terminate_when_send_terminate_msg_to_sync_sut)
{
    commander.send(DUMMY_SEND_MSG(Terminate));

    commander.recv(DUMMY_RECV_MSG(Terminate));
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