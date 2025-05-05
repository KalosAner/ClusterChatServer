
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


# 新增
当服务器接收 SIGINT 信号退出时将该服务器上的所有用户设置为离线


