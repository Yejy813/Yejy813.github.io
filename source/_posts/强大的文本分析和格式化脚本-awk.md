---
title: 文本分析和格式化脚本-Awk
date: 2019-04-03 20:50:27
tags: script
---

## Awk 简介
{% fullimage https://github.com/Yejy813/pictures/blob/master/%E6%80%A7%E8%83%BD%E5%B7%A5%E5%85%B7/awk.png?raw=true, alt, Awk工作流程图 %}

{% note warning %} **有时候，我们需要非常强有力的工具，来控制和处理我们的数据文件，达到对文件进行分析、统计、格式化输出的效果，没错，`Awk` 就是这样一款工具。** {% endnote %}
<!-- more -->

`awk` 命令或 `GNU awk` 提供了用于处理文本的脚本语言。使用 `awk` 脚本语言，您可以进行以下操作：
> 定义变量。
> 使用字符串和算术运算符。
> 使用控制流和循环。
> 生成格式化报告。

当然，我们可以使用 `awk` 处理包含数百万行的日志文件，以输出可以从中受益的可读报告，除此之外，在`Linux`下，当你想要对文本进行其他非常细致的处理，`awk`基本都可以很好的胜任，特别是当它与`sed` `grep` 配合起来，可以对文件进行全方位的分析处理。

官方手册:
> **https://www.gnu.org/software/gawk/manual/html_node/index.html#SEC_Contents**


## Awk Options (选项参数)
`awk` 命令使用如下：
```shell
$ awk options program file
```
我们可以携带以下选择参数：
```shell
-F fs     To specify a file separator. 分隔符

-f file     To specify a file that contains awk script. 脚本文件

-v var=value     To declare a variable. 变量
```

我们接下来将看到如何使用 `awk`处理文件和打印结果。

## Read Awk Scripts (脚本读取)
我们要定义一个 `awk` 脚本，我们需要使用**单引号括起来的大括号**，如下所示：
```shell
echo 'this is a test' | awk '{print $3}' # 打印 a
```
使用`echo`输出一句话，然后通过 `|` 管道执行 `awk` 指令，打印出第三个字段（Fileds）。

## Using Variables (变量)

使用 `awk`，您可以处理文本文件。 `Awk` 为找到的每个数据字段分配一些变量：
> * $0 for the whole line.
> * $1 for the first field.
> * $2 for the second field.
> * $n for the nth field.

像空格或制表符这样的空白字符是`awk`中字段之间的默认分隔符。

我们看下这个示例，看下`awk`如何处理它：
```shell
[root@yejy myshare]# cat myfile 
This is a test.
This is the second test.
This is the thrid test.
This is the fourth test.
[root@yejy myshare]# 
[root@yejy myshare]# awk '{print $1}' myfile 
This
This
This
This
[root@yejy myshare]# 
```
上面这个示例会打印出每一行的第一个字段（filed）。

有时某些文件中的分隔符不是空格，也不是制表符，而是其他内容。 您可以使用`-F`选项指定它：
```
[root@yejy myshare]# awk -F : '{print $1}' /etc/passwd
root
bin
daemon
adm
lp
sync
shutdown
halt
mail
operator
games
ftp
nobody
systemd-bus-proxy
systemd-network
dbus
polkitd
abrt
unbound
```
这个命令打印 `passwd` 文件中的第一个字段。 我们使用冒号作为分隔符，因为 `passwd` 文件使用了它。

## Using Multiple Commands (多命令)
要运行多个命令，请使用分号分隔它们，如下所示：
```shell
-bash-4.2$ echo "hello yejy" | awk '{$2="daianqi"; print $0}'
hello daianqi
```
第一个命令使`$2`字段等于`yejy`，第二个命令打印整行。

## Reading The Script From a File (文件中读取 awk 脚本)
我们可以在文件中写入 `awk` 脚本，并使用 `-f` 选项指定该文件执行。
```shell
-bash-4.2$ cat testfile 
{
    print $1 " home at " $6
}
-bash-4.2$ awk -F: -f testfile /etc/passwd                   
root home at /root
bin home at /bin
daemon home at /sbin
adm home at /var/adm
lp home at /var/spool/lpd
sync home at /sbin
shutdown home at /sbin
halt home at /sbin
mail home at /var/spool/mail
```
这里我们从 `/etc/passwd` 打印用户名和他的主路径，当然分隔符是用冒号 `-F`。

你也可以像这样写 `awk` 脚本文件：
```shell
{
  text = $1 " home at " $6
  print text  
}
```
## Awk Preprocessing (预处理)
如果您需要为结果创建标题, 您可以使用 `BEGIN` 关键字来实现此目的, 它在处理数据之前运行：
```shell
-bash-4.2$ awk 'BEGIN{print "Report Title"}{print $0}' myfile
Report Title
This is a test.
This is the second test.
This is the thrid test.
This is the fourth test.
```
## Awk Postprocessing (后期处理)
要在处理数据后运行脚本，请使用`END`关键字：
```shell
-bash-4.2$ awk 'BEGIN{print "Report Title"} {print $0} END{print "file footer"}' myfile 
Report Title
This is a test.
This is the second test.
This is the thrid test.
This is the fourth test.
file footer
-bash-4.2$ 
```
这个很有用，我们可以用这个来添加页脚。
我们把这些集合在一起，写到一个脚本文件里面：
```shell
BEGIN{
print "Users and thier corresponding home"
print " UserName \t HomePath"
print "___________ \t __________"
FS=":"
}

{
print $1 " \t " $6
}

END{
print "the end"
}
```
首先，使用 `BEGIN` 关键字创建顶部。 然后我们定义`FS`并在末尾打印页脚。

```
-bash-4.2$ awk -f testfile /etc/passwd
Users and thier corresponding home
 UserName        HomePath
___________      __________
root     /root
bin      /bin
daemon   /sbin
adm      /var/adm
lp       /var/spool/lpd
sync     /sbin
shutdown         /sbin
halt     /sbin
mail     /var/spool/mail
operator         /root
games    /usr/games
ftp      /var/ftp
```
## Built-in Variables (内建变量)
我们看到数据字段变量 `$1，$2，$3` 等用于提取数据字段，我们还处理字段分隔符 `FS`。`awk`的内建变量其实还有很多。
下面列举一些比较常见的：
> * FIELDWIDTHS &emsp;&emsp;    Specifies the field width.
> * RS          &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;    Specifies the record separator.
> * FS          &emsp;&emsp;&emsp;&emsp;    Specifies the field separator.
> * OFS         &emsp;&emsp;    Specifies the Output separator.
> * ORS         &emsp;&emsp;    Specifies the Output separator.

默认情况下，`OFS`变量是空格，您可以设置 `OFS` 变量以指定所需的分隔符：
```
-bash-4.2$ awk 'BEGIN{FS=":"; OFS="-"} {print $1,$6,$7}' /etc/passwd
root-/root-/bin/bash
bin-/bin-/sbin/nologin
daemon-/sbin-/sbin/nologin
adm-/var/adm-/sbin/nologin
lp-/var/spool/lpd-/sbin/nologin
sync-/sbin-/bin/sync
shutdown-/sbin-/sbin/shutdown
halt-/sbin-/sbin/halt
mail-/var/spool/mail-/sbin/nologin
operator-/root-/sbin/nologin
games-/usr/games-/sbin/nologin
ftp-/var/ftp-/sbin/nologin
nobody-/-/sbin/nologin
systemd-bus-proxy-/-/sbin/nologin
systemd-network-/-/sbin/nologin
```

有时，字段是在没有固定分隔符的情况下分发的。 在这些情况下，`FIELDWIDTHS`变量解决了这个问题。
假如我们有这样一个文件：
```shell
-bash-4.2$ cat myfile 
1235.96521 
927-8.3652
36257.8157
```
看下处理结果：
```
-bash-4.2$ awk 'BEGIN{FIELDWIDTHS="3 4 3"} {print $1,$2,$3}' myfile 
123 5.96 521
927 -8.3 652
362 57.8 157
```
看看输出，输出字段为每行3个，每个字段长度基于`FIELDWIDTH`指定的内容。

假设您的数据分布在不同的行上，如下所示：
```
-bash-4.2$ cat myfile 
person Name 
123 High Street
(222) 466-1234
   

Another person
487 High Street
(523) 643-8754
```
在上面的示例中，`awk`无法正确处理字段，因为字段是换行符而不是空格分隔。
您需要将`FS`设置为换行符`（\n）`并将`RS`设置为空白文本，因此空行将被视为分隔符。

是不是很棒，我们可以正确阅读记录(`record`)和字段(`filed`)。

## More Variables (更多变量)
还有一些其他变量可以帮助我们获取更多信息：
```SHELL
ARGC     Retrieves the number of passed parameters.

ARGV     Retrieves the command line parameters.

ENVIRON     Array of the shell environment variables and corresponding values.

FILENAME    The file name that is processed by awk.

NF     Fields count of the line being processed.

NR    Retrieves total count of processed records.

FNR     The record which is processed.

IGNORECASE     To ignore the character case.
```

看下这条指令：
```SHELL
-bash-4.2$ awk 'BEGIN{print ARGC,ARGV[1]}' myfile
2 myfile
```

其实很好理解，每个进程执行的时候，都会带参数，和`C`语言的`main`函数带的参数是一致的。`ARGC` 参数个数，`ARGV` 二阶字符数组，打印具体参数。

`ENVIRON`变量检索`shell`环境变量，如下所示：
```SHELL
-bash-4.2$ awk 'BEGIN{print ENVIRON["PATH"]}'
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin
```

我们可以使用没有`ENVIRON`变量的`bash`变量，如下所示：
```
-bash-4.2$ echo | awk -v home=$HOME '{print "my home is " home}'
my home is /home/willy
```

`NF`变量指定记录中的最后一个字段，但不知道其位置：
```
-bash-4.2$ awk 'BEGIN{FS=":"; OFS="-"}{print $1,$(NF-1)}' /etc/passwd
root-/root
bin-/bin
daemon-/sbin
adm-/var/adm
lp-/var/spool/lpd
sync-/sbin
shutdown-/sbin
halt-/sbin
mail-/var/spool/mail
operator-/root
games-/usr/games
ftp-/var/ftp
nobody-/
systemd-bus-proxy-/
systemd-network-/
```

让我们看看这个例子来了解 `FNR` 和 `NR` 变量之间的区别：
```
-bash-4.2$ awk 'BEGIN{FS=","}{print $1 "FNR = " FNR "  NR = " NR}' myfile myfile 
person Name FNR = 1  NR = 1
123 High StreetFNR = 2  NR = 2
(222) 466-1234FNR = 3  NR = 3
Another personFNR = 4  NR = 4
487 High StreetFNR = 5  NR = 5
(523) 643-8754FNR = 6  NR = 6
person Name FNR = 1  NR = 7
123 High StreetFNR = 2  NR = 8
(222) 466-1234FNR = 3  NR = 9
Another personFNR = 4  NR = 10
487 High StreetFNR = 5  NR = 11
(523) 643-8754FNR = 6  NR = 12
```

在此示例中，`awk`命令定义了两个输入文件, 相同的文件，但处理了两次, 输出是第一个字段值和`FNR`和`NR`变量。很容易可以看出，`NR`是当前正在处理的`record`的总序列数，`FNR`则在到达第二个文件时，`FNR`变量会变成1，`NR`不会。

## User Defined Variables（自己定义的变量）
变量名可以是任何名称，但它不能以数字开头。和`shell`脚本基本一致，如下所示：
```
-bash-4.2$ awk 'BEGIN{test="this is a test"; print test}'
this is a test
```
## Structured Commands（类 C 语言）
`awk` 脚本语言支持 `if` 条件语句、`While`、`for`循环（其中也支持`break`），以及格式化输出`printf`，和`C`语言基本一致，这个就不详细介绍了，注意换行就行，避免出现格式错误。

`myfile`包含以下内容：
```
-bash-4.2$ cat myfile 
10

15

6

33

45

-bash-4.2$ awk '{if($1 > 30){print $1}}' myfile 
33
45
```
如果要加入其它分支，可以这样：
```
-bash-4.2$ awk '{if($1 > 30){print $1}else{x = $1 / 2; print x}}' myfile            
5
0
7.5
0
3
0
33
0
45
```
写法不太美观，如果在文件中写，需要分行。

比如：
```
// 格式化输出
awk 'BEGIN{
 
x = 100 * 100
 
printf "The result is: %e\n", x
 
}'

// while 循环
awk '{
 
tot = 0
 
i = 1
 
while (i < 5)
 
{
 
tot += $i
 
if (i == 3)
 
break
 
i++
 
}
 
average = tot / 3
 
print "Average is:",average
 
} myfile

// for循环
awk '{
 
total = 0
 
for (var = 1; var < 5; var++)
 
{
 
total += $var
 
}
 
avg = total / 3
 
print "Average:",avg
 
}' myfile
```

## Built-In Functions （内建函数）
这个内建函数需要我们自己去了解熟悉，`awk` 为我们提供了数学计算，字符串处理等，如果想深入了解，可以查看[官方手册](https://www.gnu.org/software/gawk/manual/html_node/Built_002din.html#Built_002din)。除了内建函数，我们也可以自定义函数，方式和`shell`一致。

比较常用的如下：
```
数学：
sin(x) | cos(x) | sqrt(x) | exp(x) | log(x) | rand()

字符串：
length() | substr() | sprintf() |  match() | tolower() | toupper()

```

## 总结
总的来说，`awk` 是一种非常人性化的语言，吸收了`C`语言的结构控制、格式化输出等特性，很多时候写着写着会感觉是在写`C`语言，然后又兼具脚本语言的特性（临时解析执行，命名方便、快速开发等），功能也较全面，如果你是在`Linux` 下从事开发工作，建议你一定要学习一些 `awk`知识。







