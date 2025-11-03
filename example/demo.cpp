#include "TcpServer.h"

#include <functional>
#include <string>


class EchoServer {
public:
    EchoServer(EventLoop *loop, const InetAddress &addr, const std::string &name):
        server_(loop, addr, name), loop_(loop) {

        server_.setConnectionCallback(std::bind(&EchoServer::onConnection, this, std::placeholders::_1));
        server_.setMessageCallback(std::bind(&EchoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        server_.setThreadNum(1);
    }

    void start() {
        server_.start();
    }

private:
    void onConnection(const TcpConnectionPtr &conn) {
        if(conn->connected())
            LOG_INFO("Connection from %s is UP.", conn->peerAddress().toIpPort().c_str());
        else {
            LOG_INFO("Connection from %s is DOWN.", conn->peerAddress().toIpPort().c_str());
            conn->shutdown();
        }
    }

    void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp time) {
        std::string msg = buf->retrieveAllAsString();
        conn->send(msg);
    }

private:
    EventLoop *loop_;
    TcpServer server_;
};

int main() {
    EventLoop loop;
    InetAddress addr;
    EchoServer server(&loop, addr, "EchoServer");

    server.start();
    loop.loop();

    return 0;
}


