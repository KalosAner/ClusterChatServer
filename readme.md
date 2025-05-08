
nginx


使用
```
cd /usr/local/nginx/sbin
./nginx
netstat -tanp | grep nginx
./nginx -s reload  # 平滑加载新增配置
```

编写
```
git clone https://github.com/redis/hiredis
cd hiredis
make
make install
ldconfig /usr/local/lib
```

redis
```
redis
```

启动
```
#ChatClient port 一般是 8000，因为 nginx 端口为 8000
./bin/ChatClient ip port

# ChatServer
# 如果运行 nginx，6000 和 6002 是 nginx 监听的端口
./bin/ChatServer 6000
./bin/ChatServer 6002
# 不运行 nginx
./bin/ChatServer 8000
```

# 新增
当服务器主动退出时将该服务器上的所有用户设置为离线
优化客户端支持 Windosws 和 Linux 两种运行方式
实现异步的日志系统导出到日志文件中进行持久化

