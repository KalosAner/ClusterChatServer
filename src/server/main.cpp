#include "chatserver.hpp"
#include "chatservice.hpp"
#include "./log/log.h"
#include <iostream>
#include <signal.h>

using namespace std;

void resetHandler(int) {
    ChatService::instance()->reset();
    exit(0);
}

int main(int argc, char **argv)
{
    signal(SIGINT, resetHandler);
    EventLoop loop;
    int port = atoi(argv[1]);
    InetAddress addr(port);     // 缺省 IP 参数，默认绑定任意 IP：INADDR_ANY
    ChatServer server(&loop, addr, "ChatServer");
    Log::Instance()->init(1, "./log", ".log", 1024);
    
    server.start();
    loop.loop();

    return 0;
}