#include "HttpServer.hpp"
#include "Tokenizer.hpp"
#include <unistd.h>
#include <string.h>
HttpServer::HttpServer(string ip) : TcpConnection(ip)
{

}
void HttpServer::parseAndTryResponse(unsigned char buf[255], int result, int child_fd)
{
    string str = (char*)((&buf[0]));
    auto request = tokenize(str);
    uint64_t count = 0;
    for(auto it : request)
    {
        string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
        if(it == "GET"){
	        write(child_fd,response.c_str(),response.size() );
        }
    }
    
}

