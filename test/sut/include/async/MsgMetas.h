////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__msgcc_begin(Header)
    __field(id, LT(MAX_MSG_ID))
__msgcc_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__msgcc_begin(AccessReq)
    __sub_msg(Header, header)
    __field(capability, NE(INVALID_CAPABILITY))
__msgcc_end()

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
__msgcc_begin(AccessRsp)
    __sub_msg(Header, header)
    __field(result, OR(EQ(FAILURE), EQ(SUCCESS)))
__msgcc_end()
