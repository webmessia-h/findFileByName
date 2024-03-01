#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int numThr) : stop(false)    // create fixed quantity of threads
{
    for (int i = 0; i < numThr; i++)
    {
        threads.emplace_back([this]    // [this] to capture 'this' pointer of enclosed class
        {
             while (true)
             {
                 std::function<void()> task;    // create one empty task
                 {
                     std::unique_lock<std::mutex> lock(qMutex);
                     cond.wait(lock, [this] { return stop || !tasks.empty(); });    // if tasks not empty nor stop is true 
                     if (stop && tasks.empty())
                     {
                         return;
                     }

                     task = std::move(tasks.front());    // assign task from queue
                     tasks.pop();    // delete task from tasks queue
                 }
                 task(); 
             }
        });
    }
}

ThreadPool::~ThreadPool()    // destructor 
{
    {
        std::unique_lock<std::mutex> lock(qMutex);
        stop = true;    
    }
    cond.notify_all();    

    for (std::thread &worker : threads)
    {
        worker.join();    
    }
}

void ThreadPool::stopped()
{
    {
        std::unique_lock<std::mutex> lock(qMutex);
        stop = true;
    }
    cond.notify_all();
    exit(0);
}
