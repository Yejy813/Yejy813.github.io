---
title: GDB
date: 2019-01-23 20:53:27
tags: GNU Software
---
## **What is GDB?**

{% fullimage https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/gdb.png?raw=true, alt, gdb %}

官方文档：
> **https://sourceware.org/gdb/download/onlinedocs/**

`GDB` 是 `GNU` 项目的调试器，你可以用 `GDB` 查看另一个程序在执行过程中的内部内容, 或者在程序崩溃时，查看程序当时正在执行的操作。
<!-- more -->

><table><tr><td bgcolor=#FFFFE0>**(gdb) set print address on
>(gdb) f 0
> #0  Request::process (this=0x7fffffffe690) at /home/willy/myshare/thread-pool/DeadLock_Test/main.cpp:8
>  8	&emsp;     PosixThread::MutexLockGuard < PosixThread::MutexLock > lock(mutex_);
>(gdb) **</td></tr></table>

上述指令表示，当程序显示函数信息时，`GDB` 会显出函数的参数地址，然后调用 `f <n>` 或 `frame <n>`, 表示查看当前栈层的信息。在我看来，查看栈层信息以及打印相关变量的地址，是 `GDB` 最为有用的地方。

`GDB` 主要做四件事情(以及支持这些事情的其他事情)，来帮助你捕捉程序中的错误：
><table><tr><td bgcolor=#D1EEEE> ** 1. 启动程序，指定可能影响其行为的任何内容。
2. 使程序在指定条件下停止。
3. 当程序停止时，检查发生了什么。
4. 更改程序中的内容，以便您可以尝试纠正一个错误的影响并继续了解另一个错误。** </td></tr></table>

这些程序可能与 `GDB` 在同一台机器上，或者另一台机器（远程）或模拟器上执行。 `GDB` 可以在大多数流行的 `UNIX` 和 `Microsoft Windows` 变体上运行，也可以在 `Mac OS X` 上运行。

**What Languages does GDB Support?**
`GDB` 支持以下语言（按字母顺序排列）：
* Ada
* Assembly
* C
* C++
* D
* Fortran
* Go
* Objective-C
* OpenCL
* Modula-2
* Pascal
* Rust

## GDB 本机调试
首先我们总结一下 `GDB` 本机调试，也就是可执行程序和 `GDB` 跑在同一台机器上, 这也是我们最为常见的一种方式。
**1. 编译 GDB 可调试的程序**
我用 `GDB` 主要调试 `C/C++` 程序，为了将调试信息加到可执行文件中，我们需要用到 `gcc`编译器提供的 `-g` 参数，具体编译方法如下：

**Make**
><table><tr><td bgcolor=#FFFFE0>**g++&emsp;-g&emsp;-Wall&emsp;hello.cpp&emsp;-o&emsp;hello**</td></tr></table>

**CMake：**
><table><tr><td bgcolor=#FFFFE0>** set(CMAKE_BUILD_TYPE&emsp;"Debug")
>set(CMAKE_CXX_FLAGS_DEBUG&emsp;"$ENV{CXXFLAGS}&emsp;-O0&emsp;-Wall&emsp;-g2&emsp;-ggdb") #替换 Debug 版本参数**</td></tr></table>

### 启动
**下面是程序的启动，启动操作主要有三种：**
> 1.直接加载可执行程序
```GDB
gdb <program> # program 为你编译的可执行程序
```
> 2.调试可执行程序的同时，将 `core` 文件加入其中
```GDB
# 注意：core 文件是已经生成的 coredump，如何生成coredump后面介绍。
gdb  <program> core
```
> 3.当你调试正在运行的进程, 可以通过该指令附着（`attach`）到进程中调试。
```GDB
gdb <program> <PID>
```
当然我们也可以执行 `gdb` 指令，然后通过 `file <program>`来加载可执行程序的符号。

例如：
```
[root@yejy build]# gdb output/bin/dead_lock.exx  # 采用方式1, 直接加载可执行程序
GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-94.el7
Copyright (C) 2013 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /home/willy/myshare/thread-pool/build/output/bin/dead_lock.exx...done.
(gdb)
```

### 设置断点
```GDB
# 在进入指定函数时停住。C++ 可以使用class::function或function(type,type)格式来指定函数名。
break <function>

# 在源文件filename的linenum行处停住。
break filename：linenum

# 在源文件filename的function函数的入口处停住。
break filename：function
```

例如：
```
# 将断点设置在 main 函数
(gdb) b main # break简写
Breakpoint 1 at 0x40143d: file /home/willy/myshare/thread-pool/DeadLock_Test/main.cpp, line 25.
```
### 程序运行与单步调试
较常用指令是如下四个：
```
# 程序开始运行
run

# 恢复程序运行，直到程序结束，或是下一个断点到来。ignore-count表示忽略其后的断点次数。continue，c命令意思相同。
continue [ignore-count]
c [ignore-count]

# 单步跟踪，如果有函数调用，会进入该函数, count 表示连续执行count条，然后停止，否则一条一条执行。
step <count>

# 单步跟踪，如果有函数调用，不会进入该函数，count 同上。
next <count>
```

例如：
```
(gdb) run  # 开始执行
Starting program: /home/willy/myshare/thread-pool/build/output/bin/dead_lock.exx 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".

Breakpoint 1, main (argc=1, argv=0x7fffffffe128) at /home/willy/myshare/thread-pool/DeadLock_Test/main.cpp:25
25	  char* pBuff = nullptr;
Missing separate debuginfos, use: debuginfo-install glibc-2.17-222.el7.x86_64 libgcc-4.8.5-28.el7_5.1.x86_64 libstdc++-4.8.5-28.el7_5.1.x86_64
(gdb) n   # next简写，执行下一条
26	  *pBuff = '2';
```

### 分析栈信息
当程序运行到断点时，我们需要查看程序在哪里停住了。当程序调用了一个函数，函数的地址，函数参数，函数内的局部变量都会被压入"栈"（`Stack`）中。我们可以使用 `GDB` 命令来查看栈中的信息。

```
# 打印当前的函数调用栈的所有信息, n是一个正整数，表示打印栈顶上n层的栈信息, n可为负数，表示栈底。
backtrace <n>
bt <n>

# 查看当前栈，一般来说，程序停止时，最顶层的栈就是当前栈，如果你要查看栈下面层的详细信息，首先要做的是切换当前栈
# 例: frame 0，表示栈顶，frame 1，表示栈的第二层。
frame <n>
f <n>

# 这个命令会打印出更为详细的当前栈层的信息
# 大多都是运行时的内存地址。比如：函数地址，调用函数的地址，被调用函数的地址，
# 目前的函数是由什么样的程序语言写成的、函数参数地址及值、局部变量的地址等等
info frame
info f

# 打印出当前函数的参数名及其值。
info args

# 打印出当前函数中所有局部变量及其值。
info locals
```

测试代码：
```c++
class Request
{
public:
  void process() const __attribute__((noinline))
  {
    PosixThread::MutexLockGuard<PosixThread::MutexLock> lock(mutex_);
    // ..
    Printf();
  }

  void Printf() const __attribute__((noinline))
  {
    PosixThread::MutexLockGuard<PosixThread::MutexLock> lock(mutex_);
    // ..
  }

private:
  mutable PosixThread::MutexLock mutex_;
};

int main(int argc, char *argv[])
{
  char* pBuff = nullptr;
  *pBuff = '2';
  
  Request req;
  req.process();

  return 0;
}
```
`GDB` 调试打印：
```GDB
(gdb) backtrace # 查看所有调用栈
#0  main (argc=1, argv=0x7fffffffe128) at /home/willy/myshare/thread-pool/DeadLock_Test/main.cpp:25
(gdb) f # 查看当前调用栈
#0  main (argc=1, argv=0x7fffffffe128) at /home/willy/myshare/thread-pool/DeadLock_Test/main.cpp:25
25	  char* pBuff = nullptr;
(gdb) info f # 当前调用栈详细信息
Stack level 0, frame at 0x7fffffffe050:
 rip = 0x40143d in main (/home/willy/myshare/thread-pool/DeadLock_Test/main.cpp:25); saved rip 0x7ffff6ded445
 source language c++.
 Arglist at 0x7fffffffe040, args: argc=1, argv=0x7fffffffe128
 Locals at 0x7fffffffe040, Previous frame's sp is 0x7fffffffe050
 Saved registers:
  rbx at 0x7fffffffe038, rbp at 0x7fffffffe040, rip at 0x7fffffffe048
(gdb) info args # 函数参数
argc = 1
argv = 0x7fffffffe128
(gdb) info locals # 函数局部变量
pBuff = 0x401340 <_start> "1\355I\211\321^H\211\342H\203\344\360PTI\307\300`\030@"
req = {mutex_ = {mutex_ = {__data = {__lock = -138651536, __count = 32767, __owner = 15775487, __nusers = 0, __kind = 1, __spins = 0, __elision = 0, __list = {
          __prev = 0x40183d <__libc_csu_init+77>, __next = 0x7fffffffe040}}, 
      __size = "pX\274\367\377\177\000\000\377\266\360\000\000\000\000\000\001\000\000\000\000\000\000\000=\030@\000\000\000\000\000@\340\377\377\377\177\000", 
      __align = 140737349703792}, holder_ = 0}}
```
### 查看源码
```
# 显示程序第linenum行的周围的源程序。
list <linenum>

# 显示函数名为function的函数的源程序。
list <function>

# 设置一次默认显示源代码的行数。
set listsize <count>
```

例如：  
```
(gdb) list
23	int main(int argc, char *argv[])
24	{
25	  char* pBuff = nullptr;
26	  *pBuff = '2';
27	  
(gdb) set listsize 2 # 一次显示两行
(gdb) list
28	  Request req;
29	  req.process();
(gdb) 
```
### 设置显示选项
```
# 当程序显示函数信息时, GDB会显示出函数的参数地址.
set print address
set print address on

# printf pretty这个选项，那么当GDB显示结构体时会比较漂亮.
set print pretty on

# 当此选项打开时，GDB将用比较规整的格式来显示虚函数表.
set print vtbl <on/off>
```

例如：
```
(gdb) show print address
Printing of addresses is on.
(gdb) f  # argv 有地址
#0  main (argc=1, argv=0x7fffffffe128) at /home/willy/myshare/thread-pool/DeadLock_Test/main.cpp:25
25	  char* pBuff = nullptr;
(gdb) set print address off
(gdb) f  # argv 无地址
#0  main (argc=1, argv=) at /home/willy/myshare/thread-pool/DeadLock_Test/main.cpp:25
25	  char* pBuff = nullptr;
(gdb) 
```

### GDB 中运行 UNIX 的 shell 程序
在 `GDB` 环境中，我们可以执行 `UNIX` 的 `shell` 命令来完成一些操作, 包括 `Make/CMake`。
```
shell <command string>
```

例：
```
(gdb) shell ls  # ls指令
3rdlib	bin  CMakeCache.txt  CMakeFiles  cmake_install.cmake  DeadLock_Test  install_manifest.txt  lib	Makefile  output  src  unit_mock  unit_test
(gdb) shell cmake .. -DENABLE_DEBUG=ON -DENABLE_TEST=ON # 执行cmake指令
-- The compiler -g++ has c++1y support
Install prefix: /home/willy/myshare/thread-pool/build/output
CMAKE_CXX_FLAGS  :  -std=c++1y
CMAKE_CXX_FLAGS_DEBUG :  -O0 -Wall -g2 -ggdb
CMAKE_CXX_FLAGS_RELEASE :  -O3 -Wall
Build Type: Debug
-- Configuring done
-- Generating done
-- Build files have been written to: /home/willy/myshare/thread-pool/build
(gdb)
```
### 调试 coredump 文件
`Linux` 平台下在一个程序崩溃时，它一般会在指定目录下生成一个 `core` 文件，`core` 文件仅仅是一个内存映象(同时加上调试信息)，使用 `GDB` 来查看 `core` 文件，可以指示出导致程序出错的代码所在文件和行数。

首先我们需要生成 `core` 文件
1.查看当前系统是否能生成 `core` 文件, 如果显示为 0 则说明当前系统不会生成 `core` 文件，需要运行 `unlimited` 操作：
```
# 查看当前允许生产 core 文件大小
ulimit -c

# 将 core 文件大小设置为不限制大小
ulimit -c unlimited
```

2.设置 `core` 文件输出路径
`core` 文件默认输出到程序运行的目录，也可以更改为其他目录(目录一定要可写)：
```
echo "/tmp/core" >/proc/sys/kernel/core_pattern
```
运行以上命令后，`core` 文件会输出到 `/tmp` 目录下，名称为 `core.进程ID`，比如进程308挂掉后生成的 `core` 文件为`/tmp/core.308`。

><table><tr><td bgcolor=#54FF9F>**注：运行以上命令的 shell 一定要和运行程序的 shell 是同一个**</td></tr></table>

3.`GDB` 调试 `core` 文件
我们使用 `gdb  <program> core` 的启动方式来调试，这样等于在问题出现后，现场已经不存在的情况下，我们也可以进行调试，很管用。当然在正常系统环境中生成 `coredump` 文件的方式各有不同，原理都是获得其函数调用栈地址，然后通过 `address2line` 具体定位到某个函数，某一行代码。 

我们通过例子来说明，我在代码中加入下面两句，导致函数出现段错误：
```c++
  char* pBuff = nullptr;
  *pBuff = '2';
```
执行程序：
```
[root@yejy build]# ./output/bin/dead_lock.exx 
段错误(吐核)
[root@yejy build]# ls /tmp/core.4209 # 生成了一个 core 文件
/tmp/core.4209
[root@yejy build]# gdb output/bin/dead_lock.exx /tmp/core.4209 # 使用 gdb 执行程序并且调试 core 文件
GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-94.el7
Copyright (C) 2013 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /home/willy/myshare/thread-pool/build/output/bin/dead_lock.exx...done.
[New LWP 4209]
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".
Core was generated by `./output/bin/dead_lock.exx'.
Program terminated with signal 11, Segmentation fault.
#0  0x0000000000401449 in main (argc=1, argv=0x7ffd573c8518) at /home/willy/myshare/thread-pool/DeadLock_Test/main.cpp:26  
26	  *pBuff = '2'; # 直接就提示 26 行出现段错误
Missing separate debuginfos, use: debuginfo-install glibc-2.17-222.el7.x86_64 libgcc-4.8.5-28.el7_5.1.x86_64 libstdc++-4.8.5-28.el7_5.1.x86_64
(gdb) 
```
### 查看 C++ 对象虚函数表
我们前面在设置显示选项的时候，有设置显示虚函数表 `set print vtbl <on/off>`, 那具体是怎么查看呢？ 
步骤如下：
```
# 设置可显示
set print vtbl on

# 打印所有虚函数地址
info vtbl pObject

# 打印某一个虚函数
p /a (*(void ***)pObject)[0]@10  # /a 表示 16 进制打印；10表示打印的虚函数个数

# 查看相应地址的符号
info symbol 0x80486c8 
```

### 线程
```GDB
# 断点只对指定线程生效，该线程执行到该断点停止后，所有线程会一起停止，方便我们调试。
break <linespec> thread <threadno>
break <linespec> thread <threadno> if ...

# 上面的 threadno 是 gdb 分配的，我们可以通过下面这个查看线程 id。
info threads
```

### 查阅帮助
```
# 列出 gdb 指令种类
help

# GDB 指令详细帮助
gdb -help

# 一般指令
help <command>
```

上述讲解了在工作中最为常用的一些 `GDB` 指令，总体可以覆盖整个调试流程，当然`GDB` 还有非常多的其他指令，需要我们去发掘并使用，这个只能祈祷工作中可以多遇到些问题，然后尝试使用 `GDB` 去解决，这样我们才可以学到更多东西，掌握更多的调试手段。

如果还想更细致的了解 `GDB` 指令，可以查看如下链接：
> http://wiki.ubuntu.org.cn/index.php?title=%E7%94%A8GDB%E8%B0%83%E8%AF%95%E7%A8%8B%E5%BA%8F&variant=zh-cn
## GDB 远程调试
远程调试过程，真正的调试指令和本地调试基本一致，主要区别在于调试环境不一样，需要事先搭建。我们会用到远端系统使用的`gdbserver` 和本机使用的 `gdb`，大概介绍一下整体的流程。

### 编译 gdbserver 和 gdb
这一步需要对 `gdb` 和 `gdbserver` 做一下交叉编译，一般相应平台的`gdb`公司内部都会有编译好的，直接用就可以，如果需要编译，大致流程如下：
```
1. 将gdb-7.6.tar.gz拷贝到虚拟机/opt目录下
2. 解压缩：
cd /opt
tar -xzvf ./ gdb-7.6.tar.gz
3. 创建gdb build目录（最好一个编译器建立一个build目录，不然容易出错）
		mkdir -p xxx-gdb/build
4. 配置gdb平台参数，生成makefile
		cd xxx-gdb/build
/opt/gdb-7.6/configure --target=arm-linux-gnueabi --prefix=/opt/xxx-gdb
注：此处不用定义(--host)，host 是编译 Linux 版本的程序，会默认以 gcc 编译的，target是定义目标系统的版本
5. 编译gdb
		make&& make install

# gdbserver类似
```

### 环境配置
将 `GDB` 加入到环境变量：
```
vi /etc/profile在文件的末尾加入以下语句：
	export PATH=/opt/xxx/bin:/opt/xxx-gdb/bin/:$PATH
	保存/etc/profile文件后运行一下. /etc/profile或重新连接shell
```

### 具体使用
首先在远程调试机器上运行`gdbserver`，假设是 `mnt` 目录（该目录一般为挂载目录），2345为任意端口(保证之前没用过就行)，然后`Exe.exx` 为你需要运行的程序, 指令大概如下：
```GDB
/mnt/gdb/gdbserver localhost:2345 /mnt/bin/Exe.exx 
  
# 执行完，大概提示这个：
Process /mnt/bin/Exe.exx created; pid = 497
Listening on port 2345
```

接着在你的编译机器(可能是虚拟机或者编译服务器)上，使用 `gdb` 跑你的可执行程序，然后远程连接到远端的 `IP:port` 就可以了，大致如下所示：
```GDB
#首先使用你的 xxx-gdb 跑你的程序
xxx-gdb 

# 链接相关库，因为生产中，不可能就一个可执行程序，需要链接大量的动态库和静态库
set solib-absolute-prefix /lib/
set solib-search-path /lib/

# 加载可执行程序符号，Exe.exx 和远程服务器上执行的是同一个
file ./bin/Exe.exx

# 编译虚拟机(或编译服务器)上的 gdb 与远程机器上的 gdbserver 连接。 10.3.3.243为 IP，2345 为你设置的端口
target remote 10.3.3.243:2345

# 执行你的程序
run 或者 break function （设置断点什么的，或者直接跑）
```

**总之，远程调试主要是加入了一个`gdbserver`，用做远程系统上的服务程序，来和编译服务器上的 `gdb` 进行通信，其他调试手段和本机调试基本一致。**
## 总结
`GDB`常用知识大概就是这些，如果都掌握吸收了，一般的生产工作基本没有什么问题，可以很好的解决遇到的问题，当然这只是 `GDB` 所有内容中的一部分，没有官方文档那样细致，所以如果想要更加深入的了解其他 `GDB` 指令，请参阅[官方文档](https://sourceware.org/gdb/download/onlinedocs/)。 还有就是像前面那篇参考文章中提到的，编写 `GDB` 脚本来自动调试我们编写的程序，我觉得吧，虽然想法很美好，但是实用性可能不会太高，一个是编写调试脚本的工作成本是一个问题，然后该脚本所适用的调试场景可能也会比较特殊、通用性不够，导致整体成本会比较高。当然如果把编写调试脚本当做一种对 `GDB` 深入了解的方法，倒是非常不错，这样可以很好的提升我们的 `Debug` 能力与思维。

## 参考链接

> [http://wiki.ubuntu.org.cn/index.php?title=%E7%94%A8GDB%E8%B0%83%E8%AF%95%E7%A8%8B%E5%BA%8F&variant=zh-cn](http://wiki.ubuntu.org.cn/index.php?title=%E7%94%A8GDB%E8%B0%83%E8%AF%95%E7%A8%8B%E5%BA%8F&variant=zh-cn)
