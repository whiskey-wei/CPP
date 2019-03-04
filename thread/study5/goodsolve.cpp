#include <bits/stdc++.h>

class Application {
    std::mutex mux;
    std::condition_variable conVar;
    bool Isload;
public:
    Application() {
        Isload = false;
    }
    void loadData() {
        //sleep 1s
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Loading Data from XML" << std::endl;

        //mutex
        std::lock_guard<std::mutex> guard(mux);

        //finish loading
        Isload = true;

        //通知条件变量
        conVar.notify_one();
    }

    bool IsDataLoaded() {
        return Isload;
    }

    void mainTask() {
        std::cout << "Do something handshaking" << std::endl;

        //get lock
        //关于unique_lock https://blog.csdn.net/f905699146/article/details/74162559
        std::unique_lock<std::mutex> mlock(mux);

        //开始等待条件变量得到信号
        //wait()将在内部释放锁，并使线程阻塞
        //一旦条件变量发出信号，则恢复线程并再次获取锁
        //然后检测条件是否满足，如果条件满足，则继续，否则再次进入wait
        conVar.wait(mlock);
        std::cout << "Do Processing On loading Data" << std::endl;
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