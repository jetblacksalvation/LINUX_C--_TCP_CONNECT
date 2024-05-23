#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <string.h>


class TcpConnection 
{
public:
    using string = std::string;

    
    TcpConnection(string IpAddr)
    {
        
        connect();
    }
    TcpConnection()
    {
        this->IpAddr = getLocalIp();
        connect();
    }
    ~TcpConnection()
    {
        if( socket_fd >= 0 )
        {
        }
    }

    void connect()
    {
        this->socket_fd = GetSocketFd();
        if(this->IpAddr == "")
        {
            this->IpAddr = getLocalIp(); 
        }
        strncpy(this->full_addr.sa_data, this->IpAddr.c_str(), 14);
        
        if (bind(this->socket_fd, (struct sockaddr *) &this->socket_addr,sizeof(this->full_addr)) < 0){
            puts("ERROR on binding");
            exit(EXIT_FAILURE);
        }
        puts("NO ERR");
        
    }
    string getLocalIp(){
        struct ifaddrs *ifap, *ifa;
        struct sockaddr_in *sa;

        getifaddrs(&ifap);
        for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr == NULL)
                continue;

            // Check if it's an IPv4 interface
            if (ifa->ifa_addr->sa_family == AF_INET) 
            {
                sa = (struct sockaddr_in *) ifa->ifa_addr;

                // Check if it's not loopback and get the IP address
                if (!(ifa->ifa_flags & IFF_LOOPBACK)) {
                    
                    printf("Interface: %s\t Address: %s\n", ifa->ifa_name, inet_ntoa(sa->sin_addr));
                    return inet_ntoa(sa->sin_addr);
                }
            }
        }
        return "";
    }
    int GetSocketFd()
    {
        try
        {
            //creates a struct in the background that is used for connect/reads ...
            // ip addr is not defined just how it will comunicate...
            auto socket_fd = socket(AF_INET, SOCK_STREAM, 0);
            return socket_fd;
        }
        catch(std::runtime_error e)
        {
            std::cout<<"ERR: GetSocketFd failed with -> "<< e.what() << std::endl;
            
        }
    }
    string IpAddr; 
private:
    struct sockaddr_in socket_addr { .sin_family=AF_INET,.sin_port={ (htons((uint16_t)9999)) }, .sin_addr={.s_addr=INADDR_ANY}};
    struct sockaddr full_addr{.sa_family=AF_INET,};
    int socket_fd = -1;
};



int main(void){
    TcpConnection connect{};
}