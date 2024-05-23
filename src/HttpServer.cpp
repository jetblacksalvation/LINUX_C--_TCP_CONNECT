#include "HttpServer.hpp"
#include "Tokenizer.hpp"

HttpServer::HttpServer(string ip):TcpConnection(ip)
{

}
void HttpServer::parseClientRequest(unsigned char buf[255], int result)
{
    string str = (char*)((&buf[0]));
    auto response = tokenize(str);
    for(auto it : response)
    {
        std::cout<<it<<std::endl;
    }
    
}