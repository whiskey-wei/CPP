#include <iostream>
#include <thread>
using namespace std;

//使用对象创建线程
class  Cthread {
public:
    void operator ()() { //重载()符号
        for (int i = 0; i < 100; i++) {
            cout << "thread run\n";
        }
    }
};

int main() {
    thread tobj((Cthread()));
    for (int i = 0; i < 100; i++) {
        cout << "main run\n";
    }
    tobj.join();
    return 0;
}
