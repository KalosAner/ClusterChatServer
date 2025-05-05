#include "db.h"
#include <muduo/base/Logging.h>

static string server = "127.0.0.1";
static string user = "root";
static string password = "123456";
static string dbname = "chat";

MySQL::MySQL() 
{
    _conn = mysql_init(nullptr);
}
MySQL::~MySQL()
{
    if (_conn != nullptr) {
        mysql_close(_conn);
    }
}
bool MySQL::connect()
{
    // LOG_INFO << server << ' ' << user << ' ' << password << ' ' << dbname;
    MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(), password.c_str(), dbname.c_str(), 3306, nullptr, 0);
    if (p != nullptr) {
        // C和C++代码默认编码是ASCII，如不设置 gbk 中文会乱码
        mysql_query(_conn, "set names gbk");
        LOG_INFO << "connect mysql success!";
    }
    else {
        LOG_INFO << mysql_error(_conn);
        LOG_INFO << "connect mysql fail!";
    }
    return p;
}
bool MySQL::update(string sql) {
    if (mysql_query(_conn, sql.c_str())) {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "更新失败!";
        return false;
    }
    return true;
}
MYSQL_RES* MySQL::query(string sql) {
    if (mysql_query(_conn, sql.c_str())) {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "查询失败!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}

MYSQL* MySQL::getConnection() {
    return _conn;
}