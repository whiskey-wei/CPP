//给线程传递单个参数
#include <bits/stdc++.h>
using namespace std;

void func(int x, string str) {
    cout << "thread num is:" << x << endl;
    cout << "thread string is: " << str << endl;
}
int main() {
    int x = 10;
    string str = "test";
    thread threadobj(func, x, str);
    threadobj.join();
    return 0;
}