#include <async/AsyncSut.h>
#include <async/AsyncMsgs.h>
#include <common/config.h>
#include <ccinfra/log/log.h>
#include <dates/core/MsgCast.h>
#include <string.h>
#include <async/Invalid.h>

SUT_NS_BEGIN

AsyncSut::AsyncSut()
: client(SUT_ADDR, SUT_PORT, UDP_RECV_TIMEOUT_SECONDS)
, t(new std::thread([this]{run();}))
{
}

AsyncSut::~AsyncSut()
{
    t->join();
}

void AsyncSut::run()
{
    static U8 buffer[MAX_MSG_LENGTH] = {0};

    while(true)
    {
        S32 r = client.receive(buffer, MAX_MSG_LENGTH);

        if(r <= 0) break;

        Status status = AsyncSut::receive(((Header*)buffer)->id, buffer, r);
        if(status != CCINFRA_SUCCESS) break;
    }
}

Status AsyncSut::receive(const MsgId id, const void* data, const U32 length)
{
    INFO_LOG("SUT recv msg[%d]", id);

    switch(id)
    {
    case EVENT_ACCESS_REQ:
        handle(msg_cast<AccessReq>(data));
        return CCINFRA_SUCCESS;
    case EVENT_SUB_RSP:
        handle(msg_cast<CfgRsp>(data));
        return CCINFRA_SUCCESS;
    default:
        ERR_LOG("Error: SUT recv unrecognized msg[%d]", id);
    }

    return CCINFRA_FAILURE;
}

void AsyncSut::handle(const AccessReq& event)
{
    if(event.capability == INVALID_CAPABILITY)
    {
        AccessRsp rsp;
        rsp.result = CCINFRA_FAILURE;
        send(EVENT_ACCESS_RSP, &rsp, sizeof(rsp));
    }
    else
    {
        CfgReq cfg;
        cfg.capability = event.capability;
        send(EVENT_SUB_CFG, &cfg, sizeof(cfg));
    }
}

void AsyncSut::handle(const CfgRsp& event)
{
    AccessRsp rsp;
    rsp.result = event.result;
    send(EVENT_ACCESS_RSP, &rsp, sizeof(rsp));
}

void AsyncSut::send(const MsgId id, const void* data, const U32 length)
{
    INFO_LOG("SUT send msg[%d]", id);

    ((Header*)data)->id = id;
    doSend(data, length);
}

void AsyncSut::doSend(const void* data, const U32 length)
{
    client.send(DATES_ADDR, DATES_PORT, data, length);
}

SUT_NS_END
