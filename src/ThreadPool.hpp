#include <vector>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadPool
{
private:
    std::vector<std::thread> threads;    // vector of threads 
    std::queue<std::function<void()>> tasks;    // queue of void-function objects to assing task to
    
    std::condition_variable cond;    // condition variable to tell threads that queue is reachable to take task from
    std::mutex qMutex;    // to block acces to the queue for more than one thread simultaneously
    bool stop;

public:
    explicit ThreadPool(int numThr);    // create Thread Pool
    ~ThreadPool();

    template <class F>
    void enqueue(F &&task)    // function to enqueue tasks (pass by reference)
{
        {
            std::unique_lock<std::mutex> lock(qMutex);       
            tasks.emplace(std::forward<F>(task));
        }
        cond.notify_one();    // notify one thread about waiting task
    }
    void stopped();    
};
