#include <muduo/net/EventLoopThreadManager.h>
#include <muduo/base/Logging.h>

using namespace muduo;
using namespace muduo::net;
void EventLoopThreadManager::addEventLoop(EventLoop* loop)
{
    MutexLockGuard lock(getInstance().mutex_);
    getInstance().eventLoops_.insert({CurrentThread::tid(), loop});
}

EventLoop* EventLoopThreadManager::getEventLoop(pid_t tid)
{
    MutexLockGuard lock(getInstance().mutex_);
    if(getInstance().eventLoops_.find(tid) == getInstance().eventLoops_.end())
    {
        return nullptr;
    }
    return getInstance().eventLoops_.at(tid);
}

void EventLoopThreadManager::eraseEventLoop(pid_t tid)
{

    MutexLockGuard lock(getInstance().mutex_);
    if(getInstance().eventLoops_.find(tid) != getInstance().eventLoops_.end())
    {
        getInstance().eventLoops_.erase(tid);
    }
    else
    {
        LOG_SYSERR <<"An EventLoop has been deleted repeatedly. Is the logic wrong?";
    }
}

EventLoopThreadManager& EventLoopThreadManager::getInstance()
{
    static EventLoopThreadManager evm;
    return evm;
}