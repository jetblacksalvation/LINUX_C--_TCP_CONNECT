#ifndef TCPCONNECT_HPP
#define TCPCONNECT_HPP

#include <string>
#include <netinet/in.h>
class TcpConnection 
{
public:
    using string = std::string;

    // Constructors
    TcpConnection(std::string IpAddr);

    // Destructor
    ~TcpConnection();

    // Public member functions
    void tcpConnect();
    virtual void parseAndTryResponse(unsigned char buf[255], int result, int child_fd);
    int acceptLoop();
    int GetSocketFd();
    static string getLocalIp();
    // Public member variables
    string IpAddr; 

private:
    // Private member variables
    int sock_port = 9999;
    struct sockaddr_in socket_addr { .sin_family=AF_INET,.sin_port={ (htons((uint16_t)sock_port)) }, .sin_addr={.s_addr=INADDR_ANY}};
    struct sockaddr full_addr{.sa_family=AF_INET,};
    int socket_fd = -1;
};

#endif // TCPCONNECT_HPP
