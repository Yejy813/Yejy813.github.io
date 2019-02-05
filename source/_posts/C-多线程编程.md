---
title: C++ 多线程编程
date: 2019-01-12 19:03:08
tags: 多线程编程
---
## 多线程编程
```C++
class MutexLock
{
public:
  MutexLock();
  ~MutexLock();

  MutexLock(const MutexLock &mutex) = delete;
  MutexLock &operator=(const MutexLock &mutex) = delete;

  void lock();
  void unlock();
  bool IsLockedByThisThread() const;
  pthread_mutex_t *getPthreadMutex();

private:
  friend class Condition;

private:
  pthread_mutex_t mutex_;
  pid_t holder_;
};
```

这段时间，主要在分析和整理多线程相关的内容，主要是因为工作中我有负责部门基础库的开发维护，其中就包括线程库，然后近期要在组内做异步这一块的分享，所以也希望趁这个机会对这一块知识进行系统的梳理，然后自己也将 posix-thread 线程重新使用了一下，加深印象，基本覆盖到了相关关键接口的使用。
<!-- more -->
加上之前已经对 [线程概念](http://mikeblog.top/2018/11/09/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F-%E7%BA%BF%E7%A8%8B%E6%A6%82%E8%BF%B0-2018-11-9/)，以及 [同步和互斥](http://mikeblog.top/2018/11/18/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F-%E8%BF%9B%E7%A8%8B%E4%BA%92%E6%96%A5%E5%92%8C%E5%90%8C%E6%AD%A5-2018-11-18/) 做了一下总结，所以整体来说，对多线程已经有了一个比较系统的认识。

**具体`C`代码见**：
> **[https://github.com/Yejy813/posix-thread](https://github.com/Yejy813/posix-thread)** 

## C++ 封装 Posix-thread
最近把陈硕老师 muduo 网络库中多线程部分的代码阅读了一遍，同时把其中的 MutexLock, MutexLockGuard, Condition, AtomicIntegerT, CountDownLatch, Thread 等多线程构件代码敲了一编，同时写了一些测试程序，并将封装思路和注意点加入到注释中，相当于对多线程做了一个总结，加深了对多线程的理解。

**具体`C++`代码见**：
> **[https://github.com/Yejy813/posix-thread-cplusplus](https://github.com/Yejy813/posix-thread-cplusplus)**


## 总结
通过 posix-thread 的使用和封装，你会发现，其实多线程相关工具接口的使用并不难，只要我们提前制定好使用规则，将异步操作模块化的提供给业务层使用，提供一种异步机制，内部可能是使用线程池等方式对所有线程进行管理，就可以很好的降低多线程的使用难度，以此更好的避免多线程相关的问题；那么提供完异步机制，那就只剩一个问题，如果我们在异步中对共享资源进行访问，如何做到同步互斥，以及尽可能高的效率，这又是我们需要考虑的另一个问题，用 互斥锁，自旋锁，原子操作，还是条件变量，或者是由这些底层同步机制衍生出来的，更高级的同步构件，这些是需要我们仔细的去思考和设计的。

多线程的概念和实现就先分析这么多，后续会对 C++ 11 中提供的线程库以及 Java 多线程相关的知识进行关注和深入学习，C++ 11 中的多线程库，我觉得会是一个趋势，首先它是官方的，跨平台的，资料相应会较多，而且统一，所以会更好些 ，当然封装一套多线程库也不难，现在各个公司如果还是使用 Linux 原生的线程接口，那么各自都会根据业务需求，做不同程度的封装，这是历史原因造成的，但是我们要向前看；至于 java 多线程，主要是其对一些多线程工具类的封装思路，是值得借鉴的，C++ 多线程相关确实需要向 java 语言学习，毕竟 C++ 语言直到 C++11 才提供自己的线程库。