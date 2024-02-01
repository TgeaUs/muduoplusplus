#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
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
