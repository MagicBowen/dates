#include "AsyncSut.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

SUT_NS_BEGIN

AsyncSut::AsyncSut()
{
    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
}

AsyncSut::~AsyncSut()
{
    close(sockfd);
}

void AsyncSut::send(const EventId, const void* data, const U32 length)
{
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(50001);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sendto(sockfd, data, length, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
}


SUT_NS_END
