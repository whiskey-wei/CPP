#include <iostream>
#include <thread>
using namespace std;

//使用函数指针创建线程

void thread_func() {
    for(int i = 0; i < 100; i++) {
        cout << "thread run\n";
    }
}

int main() {
    thread tobj(thread_func);
    for (int i = 0; i < 100; i++) {
        cout << "main run\n";
    }
    tobj.join();
    cout << "exit\n";
    return 0;
}