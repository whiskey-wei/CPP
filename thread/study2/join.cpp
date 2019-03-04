#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

void func() {
    cout << "Work Thread " << this_thread::get_id() << endl;
    for(int i = 1; i < 100000; i++) {

    }
}

int main() {
    vector<thread> threadList;
    for (int i = 0; i < 10; i++) {
        threadList.push_back(thread(func));
    }
    cout << "main wait" << endl;
    for(auto val = threadList.begin(); val != threadList.end(); val++) {
        val->join();
    }
    cout << "main end" << endl;
    return 0;
}