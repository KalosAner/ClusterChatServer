#include "chatserver.hpp"
#include "json.hpp"
#include "chatservice.hpp"
#include <functional>
#include <string>

using namespace std;
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop *loop, const InetAddress &listenAddr, const string &nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop)
{
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    _server.setThreadNum(4);
}

void ChatServer::start()
{
    _server.start();
}

void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    if (!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}

void ChatServer::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    json js = json::parse(buf);
    // 通过解析 js["msgid"] 获取业务的处理函数，从而解耦网络模块代码

    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    msgHandler(conn, js, time);
}