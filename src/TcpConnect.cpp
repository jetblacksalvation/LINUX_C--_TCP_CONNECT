#include "TcpConnect.hpp"

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

    if (bind(this->socket_fd, (struct sockaddr *)&this->socket_addr, sizeof(this->socket_addr)) < 0)
    {
        std::cerr << "ERROR on binding" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "NO ERR" << std::endl;
    std::cout << "Hello, Server http://" << this->IpAddr << ":9999" << std::endl;
    listen(this->socket_fd, 1); // backlog = amount of pending requests from clients
    acceptLoop();
}

void TcpConnection::parseClientRequest(unsigned char buf[255], int result)
{
    static_assert("Virtual Function parseClientRequest must be defined.");
    throw(std::runtime_error("Virtual function must be defined."));
    // if (result >= 0)
    // {
    //     std::string str(reinterpret_cast<char *>(buf));

    //     // Do something with 'str'
    // }
}

int TcpConnection::acceptLoop()
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
        parseClientRequest(buf, read(child_fd, buf, 255));
        close(child_fd);
    }
    return EXIT_SUCCESS;
}

std::string TcpConnection::getLocalIp()
{
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;

    getifaddrs(&ifap);
    for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL)
            continue;

        // Check if it's an IPv4 interface
        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            sa = (struct sockaddr_in *)ifa->ifa_addr;

            // Check if it's not loopback and get the IP address
            if (!(ifa->ifa_flags & IFF_LOOPBACK))
            {
                std::cout << "Interface: " << ifa->ifa_name << "\t Address: " << inet_ntoa(sa->sin_addr) << std::endl;
                return inet_ntoa(sa->sin_addr);
            }
        }
    }
    return "";
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
