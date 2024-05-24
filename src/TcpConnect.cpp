#include "TcpConnect.hpp"
#include "HttpFunctionality.hpp"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <string.h>
#include <unistd.h>
void ForceConnect(int server_fd)
{
    int opt = 1; 
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
}
TcpConnection::TcpConnection(std::string IpAddr)
{
    this->IpAddr = IpAddr;
}

TcpConnection::~TcpConnection()
{
    close(this->socket_fd);
}

void TcpConnection::tcpConnect()
{
    this->socket_fd = GetSocketFd();
    // if (this->IpAddr.empty())//for debug
    // {
    //     this->IpAddr = getLocalIp();
    // }
    strncpy(this->full_addr.sa_data, this->IpAddr.c_str(), 14);
    ForceConnect(this->socket_fd);
    if (bind(this->socket_fd, (struct sockaddr *)&this->socket_addr, sizeof(this->socket_addr)) < 0)
    {
        std::cerr << "ERROR on binding" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "NO ERR" << std::endl;
    std::cout << "Hello, Server http://" << this->IpAddr << ":"<<this->sock_port << std::endl;
    listen(this->socket_fd, 1); // backlog = amount of pending requests from clients
    AcceptLoop();
}

void TcpConnection::parseAndTryResponse(unsigned char buf[255], int result, int child_fd)
{
    static_assert("Virtual Function parseAndTryResponse must be defined.");
    throw(std::runtime_error("Virtual function must be defined."));
    // if (result >= 0)
    // {
    //     std::string str(reinterpret_cast<char *>(buf));

    //     // Do something with 'str'
    // }
}

int TcpConnection::AcceptLoop()
{
    for (;;)
    {
        struct sockaddr addr;
        socklen_t addrlen = sizeof addr;

        int child_fd = accept(this->socket_fd, &addr, &addrlen);
        if (-1 == child_fd)
        {
            perror("accept() failed\n");
            return EXIT_FAILURE;
        }
        unsigned char buf[255];
        parseAndTryResponse(buf, read(child_fd, buf, 255),child_fd);
        
        close(child_fd);
    }
    return EXIT_SUCCESS;
}

std::string TcpConnection::getLocalIp()
{
    return HttpFunctionality::getLocalIp();
}

int TcpConnection::GetSocketFd()
{
    try
    {
        auto socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        return socket_fd;
    }
    catch (std::runtime_error &e)
    {
        std::cerr << "ERR: GetSocketFd failed with -> " << e.what() << std::endl;
        return -1;
    }
}
