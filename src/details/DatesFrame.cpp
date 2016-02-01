//#include "DatesFrame.h"
//#include "base/Placement.h"
//#include "details/SyncMsgQueue.h"
//#include "details/AsyncMsgQueue.h"
//#include "base/NullPtr.h"
//
//DATES_NS_BEGIN
//
//struct DatesReceiver
//{
//private:
//    Receiver receiver;
//    std::thread* t{__null_ptr__};
//};
//
//struct DatesFrameImpl
//{
//private:
//    union
//    {
//        Placement<SyncMsgQueue>  syncQueue;
//        Placement<AsyncMsgQueue> asyncQueue;
//    }msgQueue;
//
//private:
//    Sender sender;
//    Receiver receiver;
//    std::thread* t{__null_ptr__};
//};
//
//DATES_NS_END
