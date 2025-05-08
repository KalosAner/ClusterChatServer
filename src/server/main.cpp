#include "chatserver.hpp"
#include "chatservice.hpp"
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
    InetAddress addr(port);     // 缂虹渷 IP 鍙傛暟榛樿缁戝畾 INADDR_ANY
    ChatServer server(&loop, addr, "ChatServer");

    server.start();
    loop.loop();

    return 0;
}