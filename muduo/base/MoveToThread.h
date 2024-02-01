#pragma once
#include <memory>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>

using namespace muduo::net;
namespace muduo
{

class MoveThread
{
public:
    MoveThread();
    ~MoveThread();
    pid_t getId() const  noexcept;
    void start();
    void quit();
    bool isRunning() const;
    
private:
    mutable MutexLock mutex_;
    std::unique_ptr<EventLoopThread> eventLoopThread_;
    EventLoop* loop_;
    std::atomic_bool quit_;
};


class MoveThreadData
{
public:
    friend class MoveThread;
	
    MoveThreadData();
    ~MoveThreadData();
	void moveToThread(MoveThread& target) noexcept;

    const MoveThread* getMoveThread() const noexcept;
private:
    mutable MutexLock mutex_;
	MoveThread* moveThread_;
};

}

#define HAS_MOVETOTHREAD_OBJ\
    private:\
        std::shared_ptr<muduo::MoveThreadData> moveThreadData_ = std::make_shared<muduo::MoveThreadData>();\
    public:\
        void moveToThread(muduo::MoveThread& target) noexcept\
        {\
            moveThreadData_->moveToThread(target);\
        }\
        std::weak_ptr<MoveThreadData> getMoveThreadData()const noexcept\
        {\
            return moveThreadData_;\
        }\
        constexpr void ensureHasMoveToThread() noexcept;\





