#include "HttpServer.hpp"


int main(void){
    HttpServer connect(TcpConnection::getLocalIp());
    connect.tcpConnect();
}