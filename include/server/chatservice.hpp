#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>

#include "offlinemessagemodel.hpp"
#include "json.hpp"
#include "usermodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
#include "redis.hpp"

using json = nlohmann::json;

using namespace std;
using namespace muduo;
using namespace muduo::net;

using MsgHandler = std::function<void(const TcpConnectionPtr&, json&, Timestamp)>;


class ChatService
{
public:
    static ChatService* instance();
    // 登录
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 注册
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);

    // 聊天
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 客户端退出
    void clientCloseException(const TcpConnectionPtr &conn);

    // 添加好友
    void addFried(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 异常退出
    void reset();

    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 从redis消息队列中获取订阅的消息
    void handleRedisSubscribeMessage(int, string);
private:
    ChatService();
    // 消息id和处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;

    unordered_map<int, TcpConnectionPtr> _userConnMap;

    mutex _connMutex;
    // 数据操作类对象
    UserModel _userModel;

    OfflineMsgModel _offlineMsgModel;

    FriendModel _friendModel;

    GroupModel _groupModel;

    Redis _redis;
};

#endif