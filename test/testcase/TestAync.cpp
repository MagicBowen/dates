#include "gtest/gtest.h"
#include "dates/core/Runtime.h"
#include "dates/core/MsgQueue.h"
#include "dates/factory/DatesAsyncFactory.h"
#include "dates/FakeSystem.h"
#include "sut/include/common/config.h"
#include "sut/include/async/AsyncSut.h"
#include "FakeMsgs.h"

/////////////////////////////////////////////////////////
namespace
{
    void updateMsgIdOnSend(const RawMsg& msg)
    {
        ((Header*)msg.getMsg())->id = msg.getId();
    }

    void updateMsgInfoOnRecv(const size_t length, RawMsg& msg)
    {
        MsgId id = ((Header*)(msg.getMsg()))->id;
        msg.update(id, length);
    }
}

struct AsyncTest : public testing::Test
{
    AsyncTest()
    : runtime(DatesAsyncFactory::createRuntime([this](const RawMsg& msg)
                                                     {
                                                         asyncSend(msg);
                                                     },
                                               [this]()
                                                     {
                                                         asyncRecv();
                                                     }))
    , commander("commander", *runtime)
    {
    }

private:
    void asyncSend(const RawMsg& msg)
    {
        updateMsgIdOnSend(msg);
        client.send(SUT_ADDR, SUT_PORT, msg.getMsg(), msg.getLength());
    }

    void asyncRecv()
    {
        while(true)
        {
            RawMsg msg(MAX_MSG_LENGTH);

            S32 r = client.receive(msg.getMsg(), msg.getLength());
            if(r <= 0) break;

            updateMsgInfoOnRecv(r, msg);

            runtime->ROLE(MsgQueue).insert(std::move(msg));
        }
    }

protected:
    // XXX: the udp client should be initialed before dates runtime;
    // bcz the dates runs receiving thread which using the udp client!

    UdpClient client{DATES_ADDR, DATES_PORT, UDP_RECV_TIMEOUT_SECONDS};
    AsyncSut sut;

    DatesRuntime runtime;
    FakeSystem commander;

    const U32 PAYLOAD{0xabcd};
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
