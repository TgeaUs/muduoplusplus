#pragma once
#include <muduo/net/EventLoop.h>
#include <muduo/base/CurrentThread.h>
#include <muduo/base/Mutex.h>
namespace muduo
{
namespace net
{
    class EventLoopThreadManager
    { 
    public:
        EventLoopThreadManager(EventLoopThreadManager&&) = delete;
        EventLoopThreadManager(const EventLoopThreadManager&) = delete;

        // size_t size() const { return eventLoops_.size();}
        static void addEventLoop(EventLoop* loop);
        static EventLoop* getEventLoop(pid_t tid);
        static void eraseEventLoop(pid_t tid);
    private:
        ~EventLoopThreadManager() = default;
        EventLoopThreadManager() = default;
        static EventLoopThreadManager& getInstance();
        MutexLock mutex_;
        std::unordered_map<pid_t, EventLoop*> eventLoops_;
    };
}
}