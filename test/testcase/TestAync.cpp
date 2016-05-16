#include "gtest/gtest.h"
#include "dates/core/Runtime.h"
#include "dates/core/MsgQueue.h"
#include "dates/factory/DatesAsyncFactory.h"
#include "dates/FakeSystemHelper.h"
#include <dates/FakeMsgHelper.h>
#include "sut/include/common/config.h"
#include "sut/include/async/AsyncSut.h"
#include "sut/include/async/AsyncMsgs.h"
#include "sut/include/async/Invalid.h"
#include "sut/include/async/MsgccImpls.h"

USING_DATES_NS
USING_SUT_NS

/////////////////////////////////////////////////////////
namespace
{
    __def_fake_msg(EVENT_ACCESS_REQ,      AccessReq);
    __def_fake_msg(EVENT_ACCESS_RSP,      AccessRsp);
    __def_fake_msg(EVENT_SUB_CFG,         CfgReq);
    __def_fake_msg(EVENT_SUB_RSP,         CfgRsp);

    __def_fake_system_begin(Visitor)
        __msgcc_send(AccessReq)
        __msgcc_recv(AccessRsp)
    __def_fake_system_end

    __def_fake_system_begin(SubSystem)
        __could_recv(CfgReq)
        __could_send(CfgRsp)
    __def_fake_system_end

    void updateMsgId(const RawMsg& msg)
    {
        ((Header*)msg.getMsg())->id = msg.getId();
    }

    void updateMsgInfo(const size_t length, RawMsg& msg)
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
    , visitor(*runtime)
    , subSystem(*runtime)
    {
    }

private:
    void asyncSend(const RawMsg& msg)
    {
        updateMsgId(msg);
        client.send(SUT_ADDR, SUT_PORT, msg.getMsg(), msg.getLength());
    }

    void asyncRecv()
    {
        while(true)
        {
            RawMsg msg(MAX_MSG_LENGTH);

            S32 r = client.receive(msg.getMsg(), msg.getLength());
            if(r <= 0) break;

            updateMsgInfo(r, msg);

            runtime->ROLE(MsgQueue).insert(std::move(msg));
        }
    }

protected:
    // XXX: the udp client should be initialed before dates runtime;
    // bcz the dates runs receiving thread which using the udp client!

    UdpClient client{DATES_ADDR, DATES_PORT, UDP_RECV_TIMEOUT_SECONDS};
    AsyncSut sut;

    DatesRuntime runtime;
    FAKE(Visitor) visitor;
    FAKE(SubSystem) subSystem;

    const U32 CAPABILITY{0xabcd};
};

TEST_F(AsyncTest, shoud_rsp_success_to_visitor_when_sub_system_rsp_ok)
{
    visitor.send([this](FAKE(AccessReq)& req)
            {
                req.capability = CAPABILITY;
            });

    subSystem.recv([this](const FAKE(CfgReq)& cfg)
            {
                ASSERT_EQ(CAPABILITY, cfg.capability);
            });

    subSystem.send([](FAKE(CfgRsp)& rsp)
            {
                rsp.result = SUCCESS;
            });

    visitor.recv([](const FAKE(AccessRsp)& rsp)
            {
                ASSERT_EQ(SUCCESS, rsp.result);
            });
}

TEST_F(AsyncTest, shoud_rsp_fail_to_visitor_when_sub_system_rsp_fail)
{
    visitor.send([this](FAKE(AccessReq)& req)
            {
                req.capability = CAPABILITY;
            });

    subSystem.recv([this](const FAKE(CfgReq)& cfg)
            {
                ASSERT_EQ(CAPABILITY, cfg.capability);
            });

    subSystem.send([this](FAKE(CfgRsp)& rsp)
            {
                rsp.result = FAILURE;
            });

    visitor.recv([this](const FAKE(AccessRsp)& rsp)
            {
                ASSERT_EQ(FAILURE, rsp.result);
            });
}

TEST_F(AsyncTest, shoud_rsp_fail_to_visitor_when_recv_invalid_capability)
{
    visitor.send([this](FAKE(AccessReq)& req)
            {
                req.capability = INVALID_CAPABILITY;
            });

    visitor.recv([this](const FAKE(AccessRsp)& rsp)
            {
                ASSERT_EQ(FAILURE, rsp.result);
            });
}

TEST_F(AsyncTest, shoud_be_in_correct_state_of_the_msg_queue)
{
    visitor.send(DUMMY_SEND_MSG(AccessReq));

    sleep(UDP_RECV_TIMEOUT_SECONDS);

    ASSERT_FALSE(runtime->ROLE(MsgQueue).isEmpty());

    runtime->ROLE(MsgQueue).clear();

    ASSERT_TRUE(runtime->ROLE(MsgQueue).isEmpty());
}


