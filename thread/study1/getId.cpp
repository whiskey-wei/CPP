#include <iostream>
#include <thread>
using namespace std;

void func_thread() {
    cout << this_thread::get_id() << endl;
}

int main() {
    thread tobj1(func_thread);
    thread tobj2(func_thread);
    cout << "obj1 id: " << tobj1.get_id() << endl;
    cout << "obj2 id: " << tobj2.get_id() << endl;
    tobj1.join();
    tobj2.join();
    return 0;
}