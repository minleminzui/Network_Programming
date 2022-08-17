# 一 理解网络编程和套接字
## 1.1 理解网络编程和套接字
- 网络编程中`接受`连接请求的套接字创建过程：
    - 调用socket函数创建套接字
    - 调用bind函数分配IP地址和端口号
    - 调用listen函数转为可接受请求状态
    - 调用accept函数受理连接请求
    - `如果启动了server，不能够立即重启服务端`
- `客户端`创建套接字的过程：
    - 调用socket函数和connect函数
    - 与服务端共同运行以收发字符串数据
## 1.2 基于Linux的文件操作
>在Linux中不区分`套接字`与`文件`，或则说套接字是一种文件
## 问题
- `套接字编程`与`网络编程`的联系
    - OS提供套接字(socket),套接字是网络传输的软件设备，所以`网络编程`就是`套接字编程`
- `底层文件IO(比如open)`与`ANSI标准的IO(比如fopen的区别)`
    - 文件I/O 又称为低级磁盘I/O，遵循POSIX相关标准。任何兼容POSIX标准的操作系统上都支持文件I/O。标准I/O被称为高级磁盘I/O，遵循ANSI C相关标准。只要开发环境中有标准I/O库，标准I/O就可以使用。（Linux 中使用的是GLIBC，它是标准C库的超集。不仅包含ANSI C中定义的函数，还包括POSIX标准中定义的函数。因此，Linux 下既可以使用标准I/O，也可以使用文件I/O）。
    - 通过文件I/O读写文件时，每次操作都会执行相关系统调用。这样处理的好处是直接读写实际文件，坏处是频繁的系统调用会增加系统开销，标准I/O可以看成是在文件I/O的基础上封装了缓冲机制。先读写缓冲区，必要时再访问实际文件，从而减少了系统调用的次数。
    - 文件I/O中用文件描述符表现一个打开的文件，可以访问不同类型的文件如普通文件、设备文件和管道文件等。而标准I/O中用FILE（流）表示一个打开的文件，通常只用来访问普通文件。
    - `底层IO`是系统调用，`文件IO`是函数，为了可移植性，因为库函数是对系统调用的封装，最好不要直接使用`系统调用`
# 二 套接字类型与协议设置
- TCP套接字和UDP套接字不会共用端口号，也即如果某TCP套接字使用9190端口，那么其他TCP套接字无法使用该端口号，但是UDP套接字可以使用
- 主流intel/AMD CPU是使用`小端序`，而网络传输数据采用`大端序`，大小端转换函数,其中`h`表示`host`，`n`表示`network`，`s`表示`short`(常用于端口转换)，`l`表示`long`（常用于IP地址转换，linx中long占4个字节)，**在本身就是大端的机器上，不会发生变化**：
    - unsigned short htons(unsigned short);
    - unsigned short ntohs(unsigned short);
    - unsigned long htons(unsigned long);
    - unsigned long ntohs(unsigned long);
- 除了向`sockaddr_in`填充数据之外，在传输数据的时候，不需要转换`大小端`。
- `in_addr_t inet_addr(const char * string)`用来将点分十进制转为`uint32_t`,并且会`检查错误`
- `int inet_aton(const char * string, struct in_addr * addr)`,也是将点分十进制转换为`uint32_t`，并且会将数据存储在`addr`中。
- `char *inet_ntoa(struct in_addr adr)`,此函数是将`uint32_t`转换为点分十进制，多次调用，需要将返回的char*的字符串拷贝，不然第二次调用会被覆盖。
- `addr.sin_addr.s_addr = htol(INADDR_ANY)`表示可以监听宿主机上的任意NIC的IP
## 四 基于TCP的服务器端/客户端(1)
- `网络编程的大部分内存就是设计并实现应用层协议`
- listen函数就是创建一个可以接受请求`服务端套接字`，该套接字相当于一个门，listen的第二个参数决定了`连接请求队列的大小`
- 由于`服务端套接字`需要当门卫，那么每次`accept`的时候需要创建`新的套接字`，用来与客户端连接
# 参考
- [《TCP/IP网络编程》，作者尹圣雨](https://book.douban.com/subject/25911735/)