---
title: 使用 protobuf 进行数据序列化
date: 2020-04-25 16:48:11
tags: 网络编程
---

## protobuf 介绍

{% note warning %} **protocol buffers 是Google出品的一种语言无关、平台无关、可扩展的序列化结构数据的方法，主要用于网络数据通信、数据存储等，相对于 xml、json 等结构化数据，它更小，更快，更简单。** {% endnote %}

<!-- more -->

**protobuf 优点：**
>* 语言无关，平台无关，提供了各语言各平台的 `protobuf` 编译器，可以将写的 `.proto` 配置文件编译成对应语言的源代码
>* 高效。相比 `xml`，`json`，占用空间更小，解析速度更快，表达方式更简单
>* 可灵活扩展, 写好的 `.proto` 配置文件，后续进行数据扩展时，不会影响旧的源码程序

**protobuf 缺点**
>* 相对于 `xml` 和 `json`，可读性、可理解度上差一些，因为毕竟和程序联系比较紧密，需要进行转化和配置，对于软件工程师来说，这不算缺点。

**protobuf 相关资料：**
如果需要查看官方文档，可以参考 `Google` 开发者中心和 `github` 上开源项目。

**开发者中心**
> https://developers.google.cn/protocol-buffers

**github**
> https://github.com/protocolbuffers/protobuf

## protobuf 编译器安装
官方安装步骤：https://github.com/protocolbuffers/protobuf/blob/master/src/README.md， 按照这个来走一遍就可以了，我安装的是 `Linux` 系统 `protobuf` 库，其他系统的上面也有。

## C++ 代码测试
我们先写一个 `.proto` 配置文件 `protobuf_test.proto`: 
```
syntax = "proto3";

package tutorial;

message Person {
  string name = 1;
  int32 id = 2;
  string email = 3;

  enum PhoneType {
    MOBILE = 0;
    HOME = 1;
    WORK = 2;
  }

  message PhoneNumber {
    string number = 1;
    PhoneType type = 2 [default = HOME];
  }

  PhoneNumber phones = 4;
}
```

编译过程中我们使用如下指令，将该文件转换成 `C++` 源码, 如果是 `cmake`，可以使用`ADD_CUSTOM_COMMAND`写一个自定义指令。
> protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/addressbook.proto

在配置文件目录执行：
>  protoc -I=./ --cpp_out=./ ./protobuf_test.proto

最终生成了 `protobuf_test.pb.cc` 和  `protobuf_test.pb.h`文件，主要代码如下：
```C++
  enum : int {
    kNumberFieldNumber = 1,
    kTypeFieldNumber = 2,
  };
  // string number = 1;
  void clear_number();
  const std::string& number() const;
  void set_number(const std::string& value);
  void set_number(std::string&& value);
  void set_number(const char* value);
  void set_number(const char* value, size_t size);
  std::string* mutable_number();
  std::string* release_number();
  void set_allocated_number(std::string* number);
```
对于 `message` 每个成员都有一个 `set` 和 `get` 接口来设置和获取值。

我们写个测试程序来试用一下，看官方的文档，有几个可选的序列化接口需要注意，这个是将 `protobuf` 结构化数据转换成我们代码中常见的字符串和输入输出流：
```C++
bool SerializeToString(string* output) const; //serializes the message and stores the bytes in the given string. Note that the bytes are binary, not text; we only use the string class as a convenient container.
bool ParseFromString(const string& data); //parses a message from the given string.
bool SerializeToOstream(ostream* output) const; //writes the message to the given C++ ostream.
bool ParseFromIstream(istream* input); //parses a message from the given C++ istream.
```

测试代码如下：
```C++
#include "protobuf_test.pb.h"
#include <iostream>
#include <fstream>

int main()
{
    tutorial::Person ps;
    ps.set_name("mike"); // name
    ps.set_email("xxxxxx@qq.com"); // email
    ps.set_id(666); // id

    // set phome number
    tutorial::Person_PhoneNumber* person_num = new tutorial::Person_PhoneNumber();
    person_num->set_number("12345678910");
    person_num->set_type(tutorial::Person_PhoneType::Person_PhoneType_HOME);

    ps.set_allocated_phones(person_num);
    std::string strFile = "person.txt";
    std::fstream output(strFile, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!ps.SerializeToOstream(&output)) {
      std::cerr << "Failed to write address book." << std::endl;
      return -1;
    }
    output.close();

    // Serialize from file
    tutorial::Person ps_from;

    std::fstream input(strFile, std::ios::in | std::ios::binary);
    if (!ps_from.ParseFromIstream(&input)) {
      std::cerr << "Failed to parse address book." << std::endl;
      return -1;
    }

    std::cout << "parse from input stream. name: " << ps_from.name() 
              << " email: " << ps_from.email()
              << " phone numb: " << ps_from.phones().number()
              << std::endl;  

    input.close();
    return 0;
}
```

打印结果：
```SHELL
bash-4.2$ ./protobuf_test
parse from input stream. name: mike email: xxxxxx@qq.com phone numb: 12345678910
```

上面程序很简单，我们先创建一个 `person` 的数据结构，然后序列化到输出流保存到文件中，然后我们再创建一个 `person` 的结构对之前生成的文件进行反序列化，可以正常得到原来的内容。

需要注意的是，代码除了需要依赖 `libprotobuf.so` 外，还要记得依赖 `pthread` 库，要不然运行时会报错。

## 总结
思考一下，相对 `xml` 和 `json`，`protobuf` 除了上面列的那些优点外，在代码部署层面其实没有很大的差异，`xml` 和 `json` 需要依赖各自开源库来实现序列化操作，之前用的比较多的，`json` 是 `rapidjson`库，`xml` 是 `pugixml` 库，而`protobuf` 只是多了安装编译程序，生成对应语言代码这一流程。因此，在开发过程中，如果遇到对性能要求比较高的场景（如高性能服务器相关的`RPC`等），还是十分推荐使用 `protobuf` 做为数据序列化工具的。



