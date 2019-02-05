---
title: MakeFile 编写
date: 2019-01-20 06:33:40
tags: 
    - 编译 (compile)
    - GNU Software
---

## 程序的编译与链接
```MakeFile
# Top level makefile, the real shit is at src/Makefile

default: all

.DEFAULT:
	cd src && $(MAKE) $@

install:
	cd src && $(MAKE) $@

.PHONY: install

```

{% note warning %} **GNU Make 是一个工具，它从程序的源文件中控制程序的可执行文件和其他非源文件的生成。** {% endnote %}
<!-- more -->

C、C++ 程序在编译的时候，首先要把源文件编译成中间代码文件，在 Windows 下也就是 .obj 文件， UNIX 下是 .o 文件，即 Object File，这个动作叫做编译（compile），然后再把大量的 Object File 合成执行文件，这个动作叫作链接（link）。在编译时，编译器只检测程序语法，和函数、变量是否被声明，而在链接程序时，链接器会在所有的 Object File 中找寻函数的实现，如果找不到，就会报链接错误。

**make 则是一个工具，MakeFile 类似是一个脚本文件，文件中定义了一系列的规则来告诉 make 需要如何去编译和链接程序**。
## MakeFile 概述
### MakeFile 组成
Makefile 里主要包含了五个东西：显式规则、隐晦规则、变量定义、文件指示和注释。
><table><tr><td bgcolor=#D1EEEE>**1、显式规则。显式规则说明了，如何生成一个或多个的目标文件。这是由 Makefile 的书写者明显指出，要生成的文件，文件的依赖文件，生成的命令。
>2、隐晦规则。由于我们的 make 有自动推导的功能，所以隐晦的规则可以让我们比较粗糙地简略地书写 Makefile，这是由 make 所支持的。
>3、变量的定义。在 Makefile 中我们要定义一系列的变量，变量一般都是字符串，这个有点像 C 语言中的宏，当 Makefile 被执行时，其中的变量都会被扩展到相应的引用位置上。
>4、文件指示。其包括了三个部分，一个是在一个 Makefile 中引用另一个 Makefile，就像 C语言中的 include 一样；另一个是指根据某些情况指定 Makefile 中的有效部分，就像 C 语言中的预编译#if 一样；还有就是定义一个多行的命令。
>5、注释。 Makefile 中只有行注释，和 UNIX 的 Shell 脚本一样，其注释是用“#”字符。**</td></tr></table>

还有一点需要注意，在 Makefile 中的命令，必须要以[Tab]键开始。
### MakeFile 工作方式
GNU 的 make 工作时的执行步骤如下：
><table><tr><td bgcolor=#D1EEEE>**1、读入所有的 Makefile。
>2、读入被 include 的其它 Makefile。
>3、初始化文件中的变量。
>4、推导隐晦规则，并分析所有规则。
>5、为所有的目标文件创建依赖关系链。
>6、根据依赖关系，决定哪些目标要重新生成。
>7、执行生成命令。**</td></tr></table>

## MakeFile 使用
### 书写规则
用一个示例来说明 MakeFile 的书写规则，以便给大家一个感性认识。示例来源于 gnu 的 make 使用手册，这个示例中，我们的工程有8个c文件，和3个头文件，我们要写一个 MakeFile 来告诉 make 命令如何编译和链接这几个文件。我们的规则是：

> 1）如果这个工程没有编译过，那么我们的所有c文件都要编译并被链接。
> 2）如果这个工程的某几个c文件被修改，那么我们只编译被修改的c文件，并链接目标程序。
> 3）如果这个工程的头文件被改变了，那么我们需要编译引用了这几个头文件的c文件，并链接目标程序。

MakeFile 写得够好，所有的这一切，我们只用一个 make 命令就可以完成，make 命令会自动智能地根据当前的文件修改的情况来确定哪些文件需要重编译，从而自己编译所需要的文件和链接目标程序。

**MakeFile 的书写规则**：
```MakeFile
target ... : prerequisites ...
command
...
...

```
target 也就是一个目标文件，可以是 Object File，也可以是执行文件。还可以是一个标签（Label），对于标签这种特性，在后续的“伪目标”中会有介绍。
prerequisites 就是要生成那个 target 所依赖的文件或是目标。
command 也就是 make 需要执行的命令。（任意的 Shell 命令）

><table><tr><td bgcolor=#54FF9F>**这是一个文件的依赖关系，意思是， target 这一个或多个的目标文件依赖于 prerequisites 中的文件，其生成规则定义在 command 中。说白一点就是说， prerequisites 中如果有一个以上的文件比 target 文件要新的话， command 所定义的命令就会被执行。这就是 Makefile 的规则，也就是 Makefile 中最核心的内容。**</td></tr></table>


正如前面所说的，如果一个工程有3个头文件，和8个c文件，我们为了完成前面所述的那三个规则，我们的 Makefile 如下：
{% fullimage https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/makefile.png?raw=true, alt, Makefile %}

反斜杠（\）是换行符的意思，这样比较便于makefile的易读。我们可以把这个内容保存在名字为 “makefile” 或 “Makefile” 的文件中，然后在该目录下直接输入命令 “make” 就可以生成执行文件 edit。如果要删除执行文件和所有的中间目标文件，那么，只要简单地执行一下 “make clean” 就可以了。

上图中是最原始的写法，其中有很多变量是重复出现的，我们可以新增 <font color=#dd0000>**变量**</font> 以及根据 make 的 <font color=#dd0000>**自动推导**</font>，来简化 Makefile。

引入变量objects：
![avatar](https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/makefile2.png?raw=true)

GNU 的 make 很强大，它可以自动推导文件以及文件依赖关系后面的命令，于是我们就没必要去在每一个[.o]文件后都写上类似的命令，因为，我们的make会自动识别，并自己推导命令。

只要 make 看到一个[.o]文件，它就会自动的把[.c]文件加在依赖关系中，如果 make 找到一个 whatever.o，那么 whatever.c，就会是 whatever.o 的依赖文件。并且 cc -c whatever.c 也会被推导出来，于是，我们的 makefile 再也不用写得这么复杂。

最新的 makefile：
{% fullimage https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/makefile8.png?raw=true, alt, Makefile %}
{% fullimage https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/makefile4.png?raw=true, alt, Makefile %}

<font color=#dd0000>**编译C时，<n>.o 的目标会自动推导为 <n>.c**</font>
Makefile 中
```MakeFile
main : main.o
    gcc -o main main.o
```
会自动变为:
```MakeFile
main : main.o
    gcc -o main main.o

main.o: main.c    <-- main.o 这个目标是隐含生成的
    gcc -c main.c
```

### log 打印
我们可以使用 info / warning / error 打印日志。
```MakeFile
$(error text…)
$(warning text…)
$(info text…)
# To print variables,

$(error VAR is $(VAR))
$(warning  VAR is $(VAR))
$(info VAR is $(VAR))
# when you use 'error' the make execution will stop after showing the error string
```
例如：
{% fullimage https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/makefile5.png?raw=true, alt, Makefile %}
输出：
{% fullimage https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/makefile6.png?raw=true, alt, Makefile %}

### 变量
**1. 变量赋值**
{% fullimage https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/makefile-variable1.png?raw=true, alt, Makefile %}


**2. 变量替换**
{% fullimage https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/makefile-variable2.png?raw=true, alt, Makefile %}
**3. 变量追加值 +=**
{% fullimage https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/makefile-variable3.png?raw=true, alt, Makefile %}
4.变量覆盖
{% fullimage https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/makefile-variable4.png?raw=true, alt, Makefile %}
5.目标变量
{% fullimage https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/makefile-variable5.png?raw=true, alt, Makefile %}
{% fullimage https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/makefile-variable6.png?raw=true, alt, Makefile %}

### 前缀
{% fullimage https://github.com/Yejy813/pictures/blob/master/%E7%BC%96%E8%AF%91/make-shell.png?raw=true, alt, Makefile %}

### 伪目标
“伪目标”并不是一个文件，只是一个标签，由于“伪目标”不是文件，所以 make 无法生成它的依赖关系和决定它是否要执行。为了避免和文件重名的这种情况，我们可以使用一个特殊的标记“.PHONY”来显示地指明一个目标是“伪目标”，向 make 说明，不管是否有这个文件，这个目标就是“伪目标”
```MakeFile
.PHONY: clean --> 最好加上，以免和文件名冲突
clean:
  rm *.o temp
```
伪目标同样可以作为“默认目标”，只要将其放在第一个。一个示例就是，如果你的 Makefile 需要一口气生成若干个可执行文件，但你只想简单地敲一个 make 完事，并且，所有的目标文件都写在一个 Makefile 中，那么你可以使用“伪目标”这个特性：
```MakeFile
all: prog1 prog2 prog3
.PHONY: all
prog1: prog1.o utils.o
  cc -o prog1 prog1.o utils.o
prog2: prog2.o
  cc -o prog2 prog2.o
prog3: prog3.o sort.o utils.o
  cc -o prog3 prog3.o sort.o utils.o
```

## 总结
MakeFile 主要思想就是依赖关系，判断依赖文件更新，来执行相关 command。MakeFile 对于一些工程结构简单的代码，可以很好的胜任组织编译链接工作，但是当工程非常大的时候(代码目录繁多，层次错综复杂)，手写 MakeFile 会非常麻烦，而且 MakeFile 是类 Unix 平台（平台相关）上的工具，，如果换一个平台(windows、android等)，又需要重新编写其他编译链接脚本，因此，在开发生产中，建议使用跨平台编译工具 CMake。


> **主要参考书籍 << 跟我一起写 MakeFile >> **
> **官方文档：http://www.gnu.org/software/make/manual/make.html#Reading **