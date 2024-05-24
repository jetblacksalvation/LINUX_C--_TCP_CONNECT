#include "HttpFunctionality.hpp"
#include "Tokenizer.hpp"
#include <iostream>

#include <string>
#include <ifaddrs.h>

#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>

HttpFunctionality::Dictionary 
HttpFunctionality::Dictionary::PopulateFromString(string str)
{
    _DictT DictionaryResult;


}


std::string      
HttpFunctionality::getLocalIp()
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