#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo;
using namespace muduo::net;

// 聊天服务器主类
class ChatServer
{
public:
    ChatServer(EventLoop* loop, const InetAddress& listenAddr, const string& nameArg);

    void start();

private:
    // 处理连接的回调函数
    void onConnection(const TcpConnectionPtr&);
    // 处理读写的回调函数
    void onMessage(const TcpConnectionPtr&, Buffer *, Timestamp);

    TcpServer _server;  // 组合的 muduo 库，实现服务器功能的类对象
    EventLoop *_loop;   // 指向事件循环对象的指针
};

#endif