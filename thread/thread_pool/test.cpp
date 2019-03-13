#include "threadpoll.hpp"
#include <string>

class Task {
public:
    void process() {
        cout << "run ..." << endl;
    }
};

int main() {
    threadPool<Task> pool(6);
    std::string str;
    while(1) {
        shared_ptr<Task> t(new Task());
        pool.append(t);
    }
    return 0;
}