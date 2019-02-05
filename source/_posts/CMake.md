---
title: CMake
date: 2019-01-26 22:37:26
tags: 编译 (compile)
---
## CMake 介绍

{% fullimage https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/cmake.png?raw=true, alt, CMake %}

{% note warning %} **CMake 是一个开源的跨平台工具系列，旨在构建，测试和打包软件。 CMake 用于使用简单的平台和独立于编译器的配置文件来控制软件编译过程，并生成可在你选择的编译器环境中使用的本机 makefile 和工作空间。** {% endnote %}
<!-- more -->

CMake 是个开源的跨平台自动化建构系统，它用组态文档控制建构过程（build process）的方式和 Unix 的 Make 相似，只是 CMake 的组态文档取名为 CMakeLists.txt。CMake 并不直接建构出最终的软件，而是产生标准的建构档（如 Unix 的 Makefile 或 Windows Visual C++ 的 projects/workspaces），然后再依一般的建构方式使用。这使得熟悉某个集成开发环境（IDE）的开发者可以用标准的方式建构他的软件。CMake 可以编译源代码、制作程序库、产生适配器（wrapper）、还可以用任意的顺序建构可执行文件。CMake 支持 in-place 建构（二进档和源代码在同一个目录树中）和 out-of-place 建构（二进档在别的目录里），因此可以很容易从同一个源代码目录树中建构出多个二进档。CMake 也支持静态与动态程序库的建构。

**CMake 特点主要有：**
>* 开放源代码，使用类 BSD 许可发布。 https://cmake.org/licensing
>* 跨平台，并可生成 native 编译配置文件，在 Linux/Unix 平台，生成 makefile，在苹果平台，可以生成 xcode，在 Windows 平台，可以生成 MSVC 的工程文件。
>* 能够管理大型项目。我所在公司的项目代码就是用 CMake 构建的，代码量大概 140 万行。
>* 简化编译构建过程和编译过程。CMake 的工具链非常简单：cmake+make。
>* 高效虑，相对其他构建体系，构建速度上有优势。
>* 可扩展，可以为 CMake 编写特定功能的模块，扩充 CMake 功能。

**CMake 缺点**
> CMake 很简单，但是没有想象中的简单，比如知乎网友神评论："屠龙的英雄，自己也已经成为了龙"。
> CMake 编写的过程实际就是编程的过程，我们编写的是 CMakeLists.txt (每个目录一个), 使用的是 "CMake 语言和语法"。

**项目构建步骤：**
1. 为每个代码目录编写 CmakeLists.txt。
2. 执行命令“cmake PATH”或者“ccmake PATH”生成 Makefile ( PATH 是 CMakeLists.txt 所在的目录 )。
3. 使用 make 命令进行编译。

看构建步骤是不是感觉 `CMake` 很简单，相对于 `MakeFile` 编写来说确实如此，想想看, 如果一份代码中包含数十个 Project，然后每个 Project 中文件夹数目也很多，这时候我们如果使用 `MakeFile` 构建整份代码，那我们需要编写的依赖项会十分繁重且复杂，想想都头大，但是 `CMake` 却能够通过简单且直观的 `cmake-commands` 来帮你编写出你想要的 `MakeFile` 文件，最后只需简单的执行一步 `make` 指令，便可以完成整份代码的编译。反正我自从开始写 `CMake` 以后，就不写 `MakeFile` 了。

## CMake 安装
`CMake` 目前已经成为各大 `Linux` 发行版提供的组件，基本不需要我们手动安装，`Linux` 系统下，执行 `cmake --version`，如果可以看到版本号，就说明已经安装, 如果觉得版本太旧，想要更新，可以从官网下载。
> https://cmake.org/download/

## CMake 官方文档
`CMake` 为我们提供了一个官方文档，其中将 `CMake` 整体进行了一下内容的划分，该文档可以作为我们的一个帮助手册，仅仅作为查阅指令的功能，因为官方并没有为我们提供使用的 `example`，而是提供了 `CMake` 的相关课程和书籍 << mastering CMake >>，当然这些事需要付费的。

**官方文档 (3.13版本)：**
> https://cmake.org/cmake/help/v3.13/index.html

**具体目录如下：**

**Command-Line Tools**  提供了三种命令行工具，除了cmake，还有测试和打包工具
>* cmake(1)
>* ctest(1)
>* cpack(1)

**Interactive Dialogs** 交互式对话，一般用命令行工具就够了
>* cmake-gui(1)
>* ccmake(1)

**Reference Manuals** 参考手册
>* cmake-buildsystem(7) 构建系统
>* cmake-commands(7) 指令
>* cmake-compile-features(7) 编译功能
>* cmake-developer(7) 为开发人员修改 cmake 源代码树本身以及创作外部维护模块的人员参考
>* cmake-env-variables(7) 环境变量
>* cmake-generator-expressions(7) cmake 生成器表达式
>* cmake-generators(7) cmake 生产器
>* cmake-language(7) 语言
>* cmake-modules(7) 模块
>* cmake-packages(7) 包
>* cmake-policies(7) 策略
>* cmake-properties(7) 属性
>* cmake-qt(7)  qt相关
>* cmake-server(7) 服务器
>* cmake-toolchains(7) 工具链
>* cmake-variables(7) 变量
>* cpack-generators(7) cpack 生成器

**Release Notes**
>* CMake Release Notes 发布版本说明


列出这个目录，只是为了提醒，我们需要有阅读英文文档的能力，因为开源项目基本都是以英文形式发布的，所以我们必须养成习惯，不懂得地方借助 `google` 翻译，慢慢就能看懂了。

这边有位博友翻译过，可以参考一下：
https://www.cnblogs.com/coderfenghc/archive/2012/06/16/CMake_ch_01.html
## Hello CMake
下面从最简单的程序介绍如何构建 `CMake` 工程，然后慢慢引入 `CMake` 的各项特性。
### C++代码
先使用 `CMake` 尝试构建单文件的工程，工程只有 `main.cpp` 一个文件：
```C++
#include <iostream>
int main()
{
    std::cout << "Hello CMake!" << std::endl;
    return 0;
}
```
### CMakeLists.txt
在 `main.cpp` 的同一目录下，新建一个文本文件，命名为 `CMakeLists.txt`，内容如下：
```cmake
project(Hello_CMake)
cmake_minimum_required (VERSION 2.8.12)
	
set(SRC_FILES main.cpp)

add_executable(hellocmake
    ${SRC_FILES}
    )
```
解释一下上面的 `CMake`:

><table><tr><td bgcolor=#D1EEEE>**`CMake` 中，以命令为单位执行动作，命令不区分大小写。
>`project` 命令声明工程的名称，同时会添加一些变量（支持的语言，不写默认支持所有），`CMake` 管理的每个工程都需要有 `project` 命令。
>`cmake_minimum_requried` 声明最小要求，可以是 `CMake `的版本，也可以是其他的条件，这里要求使用 `CMake` 最低版本为`2.8.12` 。
>`set` 命令用来给设置变量，`set` 的第一个参数为变量名，其后的所有参数都将放入到这个变量中，参数可以有多个，需要注意与命令不同，`CMake` 的变量是区分大小写的。
>`add_executable` 命令可以增加一个目标来生成可执行文件，第一个参数为目标名称，之后的参数为源代码文件列表，源代码可以有多个。例子中使用了变量内容作为源代码，也可以直接填上源代码路径。
>如果在 `CMakeLists.txt` 中需要引用变量中的内容，需要使用 `${Var}` 来展开，如例子中的 `${SRC_FILES}` 将会展开成`main.cpp` ，如果不使用 `${}`，`SRC_FILES` 将会被当做一般的字符串处理。**</td></tr></table>

### 编译
`CMake` 支持原地编译和分离编译两种方法编译，分离编译可以使编译中间文件和最终文件和源代码分离，便于源代码的管理，所以`CMake` 这里介绍分离编译方法。我的源代码和`CMakeLists.txt`放在`cmakedemo`目录下。

><table><tr><td bgcolor=#D1EEEE>**先将工作目录切换到源代码目录的上一层
>cd ..
>创建一个编译目录，并进入该目录
>mkdir buildcmakedemo && cd buildcmakedemo
>在该目录下使用cmake配置工程，生成makefile
>cmake ../cmakedemo
>使用make编译工程
>make
>在编译目录下就生成了hellocmake，./hellocmake可以执行。
>cmake命令可以解析CMakeLists.txt生成makefile，还可以传入给项目一些变量，控制编译过程，在后面会详细介绍。**</td></tr></table>

最终的目录结构：
```
[root@yejy cmakedemo]# tree
.
|-- buildcmakedemo # 编译目录
`-- cmakedemo  # 源代码目录
    `-- main.cpp

```
### 子目录和库
多数工程是分为多个模块的，每个模块处在不同的目录中，`CMake` 中可以使用命令 `add_subdirectory` 添加子目录，**子目录继承父目录所有的属性和变量**。现在为我们的 `HelloCMake`程序加点料。

在源代码目录新建文件夹 `child`，在 `child` 中新建源代码文件 `lib.cpp` 内容如下
```c++
#include <iostream>
void call_child()
{
    std::cout << "Oh My Lady Gaga!" << std::endl;
    return 0;
}
```
在 `child` 下创建文本文件 `CMakeLists.txt`，内容如下：
```cmake
set(SRC_FILES lib.cpp)

add_library(child
	${SRC_FILES}
)

```
`add_library` 命令与 `add_executable` 类似，但生成的是库文件，`CMake` 默认会生成静态库，如果需要生成动态库，可以目标名后添加 `SHARED` 关键字，`add_library(child SHARED ${SRC_FILES})`，这样就会生成动态库。

我们还要为 `child` 这个库提供一个头文件，在 `child` 目录下新建一个头文件`lib.h`，然后在文件中声明`call_child()`。
```c++
void call_child();
```

修改 `main.cpp` 使用 `child` 库，`main.cpp` 修改后如下：
```c++
#include <iostream>
#include <lib.h>

int main()
{
    std::cout << "Hello CMake!" << std::endl;
    call_child();
    return 0;
}
```
为了让编译器知道如何查找头文件 `lib.h` 和让连接器知道 `hellocmake` 需要库 `child`，我们需要修改根目录下的`CMakeLists.txt`：
```cmake
project(Hello_CMake)
cmake_minimum_required(VERSION 2.8.12)
	
set(SRC_FILES main.cpp)

# 新增：添加子目录的CMakeLists.txt，以及包含 child 文件目录
add_subdirectory(child)
include_directories(child)

add_executable(hellocmake
    ${SRC_FILES}
    )
    
# 新增：链接 child 库
target_link_libraries(hellocmake
    child
    )
```
解释一下上面的 `CMake`:
><table><tr><td bgcolor=#D1EEEE>**如前面提到的 `add_subdirectory` 会添加一个子目录到工程中，`CMake` 会解析子目录中的 `CMakeLists.txt` 为子目录生成`MakeFile`。
>`include_directories` 命令相当于 `gcc` 命令的 `-I`，告诉编译器到该目录中查找头文件。
>`target_link_libraries` 命令相当于`gcc`的`-l`命令，告诉连接器连接这个库，第一个参数为生成的目标名称，后面可以跟项目中其他库的目标名称或者已经存在的库文件名，查找规则和`gcc -l`一致。
>编辑完成后就可以到第三步的编译目录中再次执行 `cmake` 和 `make` 生成 `hellocmake`。这个`hellocmake`使用`child`库输出了文本`Oh My Lady Gaga!`。
> 注：当然，我们也可以使用find_package**</td></tr></table>

### 交叉编译
`CMake` 会默认使用本机的编译器来配置项目，如果需要交叉编译，需要设定变量 `CMAKE_C_COMPILE` 和 `CMAKE_CXX_COMPILE`，可以通过 `cmake` 命令的 `-D` 参数传入,`-D` 参数可以给 `CMake` 传入变量，格式为 `-DVar=Value`。切换工作目录到第三步建立的编译目录中。

执行命令:
```cmake
cmake ../cmakedemo -DCMAKE_C_COMPILER=arm-linux-gnueabi-gcc -DCMAKE_CXX_COMPILER=arm-linux-gnueabi-g++。
```
执行 `make` 编译工程，就可以在编译目录得到 `arm` 平台下的 `hellocmake` 程序。

`CMAKE_C_COMPILE`和 `CMAKE_CXX_COMPILE` 也可以在 `CMakeLists.txt` 中使用 `set`命令设定，需要注意的是，由于`project` 命令会根据这这两个变量设定一些其他的变量，所以它们应该在 `project` 命令前被设定。

修改源代码目录的 `CMakeLists.txt`：
```cmake
# 设置编译平台参数
set(CMAKE_C_COMPILER arm-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabi-g++)

project(Hello_CMake)
cmake_minimum_required(VERSION 2.8.12)
	
set(SRC_FILES main.cpp)

add_subdirectory(child)
include_directories(child)

add_executable(hellocmake
    ${SRC_FILES}
    )
    
target_link_libraries(hellocmake
    child
    )
```
到编译目录下执行 `cmake` 和 `make` 也可以得到 `arm` 平台下的 `hellocmake`。

## CMake 进阶
`CMake` 有一整套完备的编译控制体系，拥有繁多的命令和预置变量，这一节将选取一些较常用的命令做简单介绍，其具体使用和其他未介绍到的可以浏览[官方文档](https://cmake.org/cmake/help/v3.13/index.html)。官方文档详细介绍了包括 `cmake` 命令本身和 `CMakeLists.txt` 中使用的所有命令和变量。在 `cmake` 安装包中也有相应的 `man` 文档，`cmake` 命令也有`--help-command` 参数可以查阅各命令的用法。

### 通用变量
**1、CMAKE_BUILD_TYPE**
这个变量可以控制程序的生成模式，可以留空，也可以选择这四种模式：`Release`，`MinSizeRel`，`Debug`，`RelWithDebInfo`。
>	Release模式下打开-O2开关。
>	MinSizeRel模式下打开-Os开关。
>	Debug模式打开-g开关。
>	RelWithDebInfo模式同时打开-O2和-g开关。

**2、CMAKE_VERBOSE_MAKEFILE**
控制编译命令是否可见，设置这个变量为 `ON` 将会在 `make` 时看到编译命令，所有编译时加入的参数和编译的文件都将打印出来，便于校验 `CMakeLists.txt` 的正确性。

**3、CMAKE_SOURCE_DIR**
指向工程源代码根目录，如使用 `cmake ../cmakedemo` 配置工程时，`CMAKE_SOURCE_DIR` 的值就是 `../cmakedemo`的路径。

**4、CMAKE_BINARY_DIR**
指向编译目录，如前一节的例子，`CMAKE_BINARY_DIR` 的值就是 `buildcmakedemo` 的路径。

### 编译阶段命令及变量
**1、add_definitions**
添加编译器参数的命令，相当于直接在编译时直接在编译命令上添加参数，需要注意这个命令不影响链接时的参数。如使用 `g++` 编译时，添加命令`add_definitions(-std=c++11)`会让编译时使用`"g++ -std=c++11"`命令，但是连接时没有`"-std=c++11"`。 

**2、CMAKE_C_FLAGS**
这个命令也是在编译命令上添加参数，与 `add_definitions` 不同的是这个命令有兄弟命令，可以在不同模式下添加不同的参数：
>CMAKE_C_FLAGS
>CMAKE_C_FLAGS_DEBUG
>CMAKE_C_FLAGS_MINSIZEREL
>CMAKE_C_FLAGS_RELEASE
>CMAKE_C_FLAGS_RELWITHDEBINFO

分别对应所有模式、`Debug`模式、`MinSizeRel`模式、`Release`模式和`RelWithDebInfo`模式。对应 `C++` 语言的变量只要把变量名第二段的`C`换成`CXX`即可。

**3、configure_file**
这个命令用于传递CMake变量给语言，在跨平台编译中比较常用。其格式为：
```cmake
configure_file(<input> <output> [COPYONLY] [ESCAPE_QUOTES] [@ONLY] [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF]])
```
命令将会拷贝`input`到`output`并将其中的`${var}`和`@var@`换成对应`CMAKE`中的变量。由于在一些语言中`${var}`已经被占用，所以`CMake`添加了`@var@`这种表示方法，在命令中添加关键字`@ONLY`可以仅替换文件中的`@var@`，`${var}`会被忽略。

例如，我们可以在代码中这样定义：
```c++
#define HAS_BOOST   ${BOOST_FOUND}
#define HAS_PTHREAD @PTHREAD_FOUND@
```

在`CMakeLists.txt`中使用命令：
```cmake
configure_file(${CMAKE_BINARY_DIR}/cfg.h ${CMAKE_SOURCE_DIR}/cfg.in.h)
```

假设`BOOST_FOUND`和`PTHREAD_FOUND`都被定义为1，执行`cmake`后，构建目录将会生成一个`cfg.h`文件，内容为：
```c++
#define HAS_BOOST   1
#define HAS_PTHREAD 1
```

如果`configure_file`命令添加了`@ONLY`则`${BOOST_FOUND}`将会被忽略，`config.h`内容则变为：
```c++
#define HAS_BOOST   ${BOOST_FOUND}
#define HAS_PTHREAD 1
```

**4、系统变量**
><table><tr><td bgcolor=#D1EEEE>**1,`CMAKE_MAJOR_VERSION`，`CMAKE` 主版本号，比如 2.4.6 中的 2。
>2,`CMAKE_MINOR_VERSION`，`CMAKE` 次版本号，比如 2.4.6 中的 4
>3,`CMAKE_PATCH_VERSION`，`CMAKE` 补丁等级，比如 2.4.6 中的 6
>4,`CMAKE_SYSTEM`，系统名称，比如 `Linux-2.6.22`。
>5,`CMAKE_SYSTEM_NAME`，不包含版本的系统名，比如 `Linux`。
>6,`CMAKE_SYSTEM_VERSION`，系统版本，比如 2.6.22
>7,`CMAKE_SYSTEM_PROCESSOR`，处理器名称，比如 `i686`.
>8,`UNIX`，在所有的类 `UNIX` 平台为 `TRUE`，包括 `OS X` 和 `cygwin`。
>9,`WIN32`，在所有的 `win32` 平台为 `TRUE`，包括 `cygwin`。**</td></tr></table>

**5、aux_source_directory**
这个命令可以搜索某个目录所有的源代码文件，添加到变量里，其格式为`aux_source_directory(<dir> <variable>)`，多次对同一变量使用该命令，可以将不同目录的源代码都保存到变量中。对于一些在同一目录下放有很多源代码的工程，使用这个命令可以很方便地获取所有需要编译的文件。

在前一节的例子中，在源代码根目录使用命令 `aux_source_directory(. SRC_FILES)`就把`main.cpp`的路径添加到`SRC_FILES`变量中。

**6、file(GLOB_RECURSE …)**
`file`是文件操作命令，有基本的文件功能，这里介绍文件查找功能。`file`有两种模式可以查找文件，一个是`GLOB`，另一个是`GLOB_RECURSE`，`GLOB`只会查找当前目录下的文件，`GLOB_RECURSE`会查找当前目录和子目录下的文件。命令格式如下：
```CMAKE
file(GLOB variable [RELATIVE path] [globbing expressions]...)
file(GLOB_RECURSE variable [RELATIVE path] [FOLLOW_SYMLINKS] [globbing expressions]...)
```

命令默认会保存文件的绝对路径，如果需要相对路径，可以用关键字RELATIVE加上需要获取相对于哪个目录的路径来获取相对路径，但是官方不推荐获取相对路径。填写 `globbing expressions`（通配符）可以简单过滤文件。

如前一节的例子，使用 `file(GLOB SRC_FILES *.cpp)` 可以获取到 `main.cpp` 的路径，使用 `file(GLOB_RECURSE SRC_FILES *.cpp)` 可以获取到 `main.cpp` 和 `child/lib.cpp` 的路径。

### 链接阶段命令及变量

**1、CMAKE_C_LINK_FLAGES**
与 `CMAKE_C_FLAGS` 家族类似，模式下的细分变量，其内容将添加在连接器的参数上。

**2、link_directories**
设置库查找位置，相当于 `gcc` 的 `-L`，可以同时设置多个目录。

### 安装阶段命令及变量
**1、install**
大型项目中，会编译出来很多个模块，每个模块都在各自的文件夹中，不方便发布，`install` 命令可以指定目标的安装位置，`install` 可以安装多种文件，这里只介绍安装 `CMake` 目标的安装方法，`CMake` 主要有 `add_executable` 和 `add_library` 命令创建的目标，都可以使用:
```cmake
install(TARGETS target1 target2
	LIBARARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	RUNTIME DESTINATION bin)
```
这里的安装位置需要加上下面提到的变量 `CMAKE_INSTALL_PREFIX` ，默认情况下 `Linux`的 `CMAKE_INTALL_PREFIX=/usr`，使用 `make install` 命令将会把可执行文件目标安装到 `/usr/bin`下。

**2、CMAKE_INSTALL_PREFIX**
工程安装位置，为 `install` 命令使用目录的前缀，`Linux`下默认为`/usr`。

**3、CMAKE_INSTALL_RPATH**
设定安装后可执行文件的运行目录，相当于 `gcc` 的 `-Wl,rpath` 在交叉编译时比较常用。

### 分支结构和逻辑运算
`cmake`有完备的流程控制机制，有一般编程语言常用的`if`分支结构，也有`foreach`循环结构，这里介绍一下`if`分支结构，`if`用法如下：
```cmake
if(expression)
    COMMAND(ARGS ...)
elseif(expression2)
    COMMAND(ARGS ...)
else(expression)
    COMMAND(ARGS ...)
endif(expression)
```
`expressin` 填入真值表达式，变量为 **0, OFF, NO, FALSE, N, IGNORE, NOTFOUND、以-NOTFOUND结尾或未定义的值**为`false`，其他为 `true`。

注意: `else` 和`endif`的`expression`可以忽略，但是必须带上括号。
`if`内可以使用比较运算比较两个变量获得真值：
><table><tr><td bgcolor=#D1EEEE>**常用的数值运算有:
>1,`EQUAL`: 相等
>2,`LESS`：小于 
>3,`GREATER`：大于
>常用的字符串运算：
>1,`STRLESS`：字符串小于。
>2,`STRGREATER`：字符串大于
>3,`STREQUAL`：字符串等于
>4,`MATCHES`：正则表达式匹配
>此外还有文件比较等功能，可自行查阅官方文档。
>多条表达式可以使用逻辑运算NOT、AND和OR连接起来，这几个运算符优先级和C语言的逻辑运算符不同，所以推荐使用括号来明确运算顺序。**</td></tr></table>

### find_package 查找外部库
我们前面已经讲过如何链接外部库，上面提到的方法是显式调用，也就是我们知道库和头文件的位置，直接通过`include_directories`和`target_link_libraries`将库文件链接进来。现在我们介绍一下另一种方式`find_package`。

`find_package`能查找本机安装的外部库，并获取对应的环境和变量。其常用形式为：
```CMAKE
find_package(<package> [version] [REQUIRED])
```
我们以`Qt`库为例，如果需要`Qt`库，那先要使用命令`find_package(Qt4 REQUIRED)`来获取`Qt`的相关变量，由于Qt库是必须的，所以加上`REQUIRED`关键字。

`find_package`会调用`cmake`安装目录的`shared`目录下的`FindQt4.cmake`来设置`Qt`变量，同时添加一些函数和宏。使用这些变量和宏就可以编译`Qt`工程。

**系统中`FindQt4.cmake`目录:**
```
/usr/local/share/cmake-3.3/Modules/FindQt4.cmake
```

`find_package`查找`Qt`成功后，会定义一下常用变量：
```
QT_FOUND: 是否找到
QT_LIBRARIES：Qt所有库的路径，在target_link_libraries时添加。
QT_INCLUDES: Qt 头文件路径
```

对于系统预定义的 Find<name>.cmake 模块，每一个模块都会定义以下几个变量:
><table><tr><td bgcolor=#D1EEEE>**• < name>_FOUND 
>• < name>_INCLUDE_DIR or < name>_INCLUDES
>• < name>_LIBRARY or < name>_LIBRARIES 
>其中的`name`为`find_package`中的`package`参数**</td></tr></table>

找到外部模块后，我们便可以将外部模块链接进来：

```cmake
find_package(Qt4 REQUIRED)

if(QT_FOUND)
  include_directories(${QT_INCLUDE_DIR})
  target_link_libraries(${project_name} ${QT_LIBRARIES})
end()
```

## 实用的 CMake 封装
下面列一些实用的 `CMake` 封装，后续持续更新！

**1、自动检测 C++ 版本参数**
```CMAKE
# using C++ newest feature, auto test Cxx version
include(CheckCXXCompilerFlag)

foreach(cxx_feature_name "c++20" "c++2a" "c++17" "c++1z" "c++14" "c++1y" "c++11" "c++0x")
    set(cxx_feature_flag "-std=${cxx_feature_name}")
    string(REPLACE "+" "x" cxx_feature_suffix ${cxx_feature_name})
    CHECK_CXX_COMPILER_FLAG(${cxx_feature_flag} COMPILER_SUPPORTS_${cxx_feature_suffix})
    if(COMPILER_SUPPORTS_${cxx_feature_suffix})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${cxx_feature_flag}")
        message(STATUS "The compiler ${BUILDTOOL_PREFIX}-g++ has ${cxx_feature_name} support")
        break()
    endif()
endforeach()
```

**2、库文件安装**
```CMAKE
# 设置安装路径
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/output")
message("Install prefix: ${CMAKE_INSTALL_PREFIX}")

# project用的库文件安装函数
function(target_install OBJECTS)
    install(TARGETS ${OBJECTS}
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
endfunction()
```

**3、将所有包含`CMakeLists.txt`的子目录添加进来**

```CMAKE
# Add all subdirectories that exist CMakeLists.txt

include(CMakeParseArguments)
function(add_all_subdirectories)
    cmake_parse_arguments(SUBDIR "" "" "EXCLUDE" ${ARGN})
    file(GLOB ALL_FILES *)
    
    foreach(subdir ${ALL_FILES})
        if((IS_DIRECTORY ${subdir})
            AND (EXISTS ${subdir}/CMakeLists.txt))
            file(RELATIVE_PATH relPath ${CMAKE_CURRENT_SOURCE_DIR} ${subdir})
            if(SUBDIR_EXCLUDE)
                list(FIND SUBDIR_EXCLUDE ${relPath} _index)
                if (_index EQUAL -1)
                    add_subdirectory(${subdir})
                elseif(CMAKE_DEBUG)
                    message("Exclude [${relPath}] when add_all_subdirectories") 
                endif()
            else()
                add_subdirectory(${subdir})
            endif()
        endif()
    endforeach()
endfunction()
```

## 总结
`CMake` 大概就总结到这里，总的来说这个工具还是十分不错的，整体结构清晰明了，后续的话，就着力把一些好的小的功能点，封装成函数或者宏，记录下来，以后碰到需要用了，就可以直接拿来用，基本可以做到一劳永逸。

## 参考
><< cmake 实践 >>
