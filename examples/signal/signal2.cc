
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
        LOG_DEBUG <<"结果是" << g_number << " pid = " << CurrentThread::tid();
    }
};

int main()
{
    // 主线程
    muduo::Logger::setLogLevel(muduo::Logger::DEBUG);
    LOG_DEBUG << " main pid = " << CurrentThread::tid();
    muduo::net::EventLoop loop;

    //绑定槽函数关联的线程    
    SafeThread st;
    muduo::MoveThread thread1;
    muduo::sigslot::signal<> sig;
    sig.connect(&SafeThread::func, &st);
    st.moveToThread(thread1);

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