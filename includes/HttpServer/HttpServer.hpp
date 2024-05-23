#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP
#include "TcpConnect.hpp"
#include <iostream>
class HttpServer: public TcpConnection
{
public:
    using string = std::string;
    
    HttpServer(string ip);

    virtual void parseAndTryResponse(unsigned char buf[255], int result, int child_fd);
private:

};


#endif