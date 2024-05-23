#include "../includes/HttpServer/HttpServer.hpp"



int main(void){
    HttpServer connect(TcpConnection::getLocalIp());
    connect.tcpConnect();
}