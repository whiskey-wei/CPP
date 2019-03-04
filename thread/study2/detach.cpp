#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

void func() {
    for (int i = 0; i < 10; i++) {
        cout << "func" << endl;
    }
}

int main() {
    thread my_thread(func);
    my_thread.detach();
    sleep(1);
    return 0;
}