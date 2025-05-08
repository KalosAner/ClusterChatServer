因为 win 环境需要单独编译所以我把所有头文件放到一个文件夹，方便复制
编译
g++ main.cpp -o ChatClientWin -lws2_32 -std=c++20
连接：这个 IP 不可以再使用环回地址
.\ChatClientWin.exe IP PORT

Windows 默认 GBK (CP936)，所以需要把 main.cpp 重新保存为 GBK 编码