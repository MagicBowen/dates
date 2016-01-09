#ifndef H882C7C0B_EEA6_4B7D_B000_97E0576C7ED1
#define H882C7C0B_EEA6_4B7D_B000_97E0576C7ED1

#include "BaseTypes.h"
#include <netinet/in.h>

struct UdpClient
{
    UdpClient(const char* ip, const U16 port);
    ~UdpClient();

    S32 send(const char* dstIp, const U16 dstPort, const void* data, const U16 length);
    S32 receive(U8* buffer, U16 length);

private:
    struct SockAddr
    {
        SockAddr(const char* ip, const U16 port);
        const sockaddr_in& getAddr() const
        {
            return addr;
        }
    private:
        struct sockaddr_in addr;;
    };

private:
    int servSocket;
    SockAddr servAddr;
};

#endif
