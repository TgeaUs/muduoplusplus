# muduo
带有跨线程通信的muduo网络库，用信号槽实现。该代码已经用于生产环境中。

# 动机

代码在muduo-cpp17/examples/signal/signal.cc中

muduo网络库没有跨线程安全通信的机制，比如下面这段代码，两个线程对一个未用锁全局变量进行操作，这是线程不安全的。手动加锁可以解决这个问题。

我使用信号槽的机制来解决在业务层面上不用锁就可以解决跨线程通信

```c++
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoopThread.h>

using namespace muduo;
using namespace muduo::net;

int g_number = 0;


void func()
{
    for(int i = 0; i < 100000; i++)
        g_number++;
    LOG_DEBUG <<"结果是" << g_number;
}

int main()
{
    // 主线程
    muduo::Logger::setLogLevel(muduo::Logger::DEBUG);
    muduo::net::EventLoop loop;
    
    muduo::net::EventLoopThread threadLoop;
    muduo::net::EventLoopThread threadLoop2;
    auto t1 = threadLoop.startLoop();
    auto t2 = threadLoop2.startLoop();

    t1->runInLoop([&]{
        func();
    });

    t2->runInLoop([&]{
        func();
    });

    loop.loop();
    
}

```

# 信号槽的版本

代码在muduo-cpp17/examples/signal/signal2.cc中

这个版本在业务代码中(g_number++)，并没有用到锁就可以实现线程安全，最后结果是200000。 而我们初始化的代码行数仅仅只有五行。以后只需要发信号（一行代码量）就可以保证线程安全了

```c++

#include <muduo/net/EventLoopThreadManager.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Signal.h>
#include <muduo/base/MoveToThread.h>
#include <muduo/net/EventLoopThread.h>

using namespace muduo;
using namespace muduo::net;

int g_number = 0;

class SafeThread
{
    HAS_MOVETOTHREAD_OBJ
public:

    void func()
    {
        for(int i = 0; i < 100000; i++)
            g_number++;
        LOG_DEBUG <<"结果是" << g_number;
    }
};

int main()
{
    // 主线程
    muduo::Logger::setLogLevel(muduo::Logger::DEBUG);
    muduo::net::EventLoop loop;

    //绑定槽函数关联的线程    
    SafeThread st;
    muduo::MoveThread thread1;
    st.moveToThread(thread1);
    muduo::sigslot::signal<> sig;
    sig.connect(&SafeThread::func, &st);

    muduo::net::EventLoopThread threadLoop;
    muduo::net::EventLoopThread threadLoop2;

    auto t1 = threadLoop.startLoop();
    auto t2 = threadLoop2.startLoop();

    t1->runInLoop([&]{
        sig();
    });

    t2->runInLoop([&]{
        sig();
    });

    loop.loop();
}
```

# 使用方法

muduo的使用方法可以去看muduo仓库的examples的使用示例，信号槽的使用方法可以看看原作者的介绍，个人认为还是比较好懂的。

唯一需要讲的是MoveToThread类，MoveToThread类启动一个EventLoop，但是永远不会接收网络事件（未来可能把epoll_wait去掉，因为浪费描述符资源）。MoveToThread需要和一个类绑定线程，从而使信号能够发送给MoveToThread启动的线程。

类中需要定义宏HAS_MOVETOTHREAD_OBJ，让这个类有moveToThread的功能。只要这个类调用了moveToThread函数，从此以后只要是这个类对象绑定的槽函数，永远都会在MoveToThread开启的线程中执行。直到MoveToThread.quit()

```c++
class SafeThread
{
    HAS_MOVETOTHREAD_OBJ
};
SafeThread st;
muduo::MoveThread thread1; //定义一个MoveToThread类
st.moveToThread(thread1); // 讲类和线程之间绑定

// thread1.quit(); //关闭这个线程，信号发出时不会在这个线程中调用
```

# 给线程发出信号

如何使用信号槽请看原作者的[README.md](https://github.com/palacaze/sigslot/tree/master)。

我们在这里定义了信号sig，绑定了槽函数func，此时发出信号，func将在另一个线程中执行，并且多个线程发出信号是线程安全的。

```c++
class SafeThread
{
    HAS_MOVETOTHREAD_OBJ
public:

    void func()
    {
        for(int i = 0; i < 100000; i++)
            g_number++;
        LOG_DEBUG <<"结果是" << g_number;
    }
};

//绑定槽函数关联的线程    
SafeThread st;
muduo::MoveThread thread1;
st.moveToThread(thread1); //关联线程
muduo::sigslot::signal<> sig;
sig.connect(&SafeThread::func, &st); //绑定槽函数
sig(); //发出信号
```
# 注意事项

发出的信号保证在调用MoveToThread::quit()时， 先前发出的信号一定会执行，但是如果自动析构MoveToThread对象，则不保证

# 缝合的库

[信号槽](https://github.com/palacaze/sigslot/tree/master)

[muduocpp17](https://github.com/chenshuo/muduo/tree/cpp17)
