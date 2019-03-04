#include<bits/stdc++.h>

class Application {
    std::mutex mux;
    bool IsDataLoad;
public:
    Application() {
        IsDataLoad = false;
    }    
    void loadData() {
        //使该线程sleep 1s
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Load Data from json" << std::endl;
        //锁定数据
        std::lock_guard<std::mutex> guard(mux);
        //设置flag为true，数据完成加载
        IsDataLoad = true;
    }

    void mainTask() {
        std::cout << "do some Handshaking" << std::endl;
        //获得锁
        mux.lock();
        while(!IsDataLoad){
            /* 释放锁，然后等待100ms再次判断 */
            mux.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            mux.lock();
        }
        mux.unlock();
        std::cout << "Do Processing On loaded Data" << std::endl;
    }
};

int main() {
    Application app;

    std::thread thread1(&Application::mainTask, &app);
    std::thread thread2(&Application::loadData, &app);

    thread1.join();
    thread2.join();

    return 0;
}
