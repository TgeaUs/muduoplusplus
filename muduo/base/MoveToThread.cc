#include <muduo/base/MoveToThread.h>
namespace muduo
{
    
///////////////////////////////////////////////////MoveThread//////////////////////
MoveThread::MoveThread():
    eventLoopThread_(std::make_unique<EventLoopThread>()),
    loop_(eventLoopThread_->startLoop()),
    quit_(false)
{
}

MoveThread::~MoveThread()
{
}

pid_t MoveThread::getId() const noexcept
{
    // quit_用来防止重入造成死锁
    if(!quit_)
    {
        MutexLockGuard lock(mutex_);
        if(loop_ != nullptr)
        {
            return loop_->getCurrentThreadId();
        }
    }
    return -1;
}

void MoveThread::start()
{
    MutexLockGuard lock(mutex_);
    if(quit_)
    {
        assert(loop_ == nullptr);
        eventLoopThread_.reset(new EventLoopThread());
        loop_ = eventLoopThread_->startLoop();
        quit_ = false;
    }
}

void MoveThread::quit()
{
    MutexLockGuard lock(mutex_);
    if(loop_ != nullptr && quit_ == false)
    {
        loop_ = nullptr;
        quit_ = true;
        eventLoopThread_.reset();
    }

}

bool MoveThread::isRunning() const
{
    return !quit_;
}


///////////////////////////////////////////////////MoveThreadData//////////////////////
MoveThreadData::MoveThreadData():
    moveThread_(nullptr)
{

}

MoveThreadData::~MoveThreadData()
{
}

void MoveThreadData::moveToThread(MoveThread& target) noexcept
{
    MutexLockGuard lock(mutex_);
    moveThread_ = &target;
}

const MoveThread* MoveThreadData::getMoveThread()const noexcept
{
    MutexLockGuard lock(mutex_);
    return moveThread_;
}

}

