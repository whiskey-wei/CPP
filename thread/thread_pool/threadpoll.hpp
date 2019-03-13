#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <iostream>
#include <stdexcept>
#include <condition_variable>
#include <memory>
using namespace std;

const int MAX_THREADS = 1000; //线程数目

template<typename T>
class threadPool {
public:
    //构造
    threadPool(int number = 1);
    ~threadPool();
    //向任务队列中添加任务
    bool append(shared_ptr<T> &request);

private:
    //工作线程需要运行的函数
    static void* worker(void *arg);
    void run();

private:
    std::vector<std::thread> work_threads;
    std::queue<shared_ptr<T> > task_queue;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

template<typename T>
threadPool<T>::threadPool(int number) : stop(false) {
    if (number <= 0 || number > MAX_THREADS) {
        throw std::exception();
    }
    for (int i = 0; i < number; ++i) {
        std::cout << "创建第" << i << "个线程" << std::endl;
        work_threads.emplace_back(worker, this);
    }
}

template<typename T>
inline threadPool<T>::~threadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (auto &ww : work_threads) {
        ww.join();
    }
}

template<typename T>
bool threadPool<T>::append(shared_ptr<T> &request) {
    queue_mutex.lock();
    task_queue.push(request);
    queue_mutex.unlock();
    condition.notify_one();
    return true;
} 

template<typename T>
void* threadPool<T>::worker(void *arg) {
    threadPool *pool = (threadPool*) arg;
    pool->run();
    return pool;
}

template<typename T>
void threadPool<T>::run() {
    while(!stop){
        /* code */
        std::unique_lock<std::mutex> lk(this->queue_mutex);
        //unique_lock(),出作用域自动解锁
        this->condition.wait(lk, [this] {
            return !this->task_queue.empty();
            //队列不为空就停下来等待唤醒
        });
        if (this->task_queue.empty()) {
            continue;
        } else {
            shared_ptr<T> request = task_queue.front();
            task_queue.pop();
            if (request) {
                request->process();
            }
        }
    }
}