#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP
#include "TcpConnect.hpp"
#include <iostream>
class HttpServer: public TcpConnection
{
public:
    using string = std::string;
    
    HttpServer(string ip);

    virtual void parseClientRequest(unsigned char buf[255], int result);
private:

};


#endif