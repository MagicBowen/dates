#include <async/UdpClient.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

UdpClient::UdpClient(const char* ip, const U16 port, const U32 waitSeconds)
: servAddr(ip, port)
{
    servSocket = socket(PF_INET, SOCK_DGRAM, 0);
    bind(servSocket, (struct sockaddr *)&servAddr.getAddr(), sizeof(sockaddr_in));

    if(0 != waitSeconds)
    {
        struct timeval timeout={waitSeconds, 0};
        setsockopt(servSocket,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));
    }
}

UdpClient::~UdpClient()
{
    close(servSocket);
}

S32 UdpClient::send(const char* dstIp, const U16 dstPort, const void* data, const U16 length)
{
    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    SockAddr addr(dstIp, dstPort);
    sendto(sockfd, data, length, 0, (struct sockaddr *)&addr.getAddr(), sizeof(sockaddr_in));
    close(sockfd);
    return 0;
}

S32 UdpClient::receive(U8* buffer, U16 length)
{
    return recvfrom(servSocket, buffer, length, 0, NULL, NULL);
}

UdpClient::SockAddr::SockAddr(const char* ip, const U16 port)
{
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
}
