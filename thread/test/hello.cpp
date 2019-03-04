#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

mutex mux[4];
void func(int x) {
    mux[x].lock();
    printf("hello\n");
    mux[x].unlock();
    for(int i = 0; i < 4; i++) {
        mux[i].lock();
    }
    printf("world\n");    
    for(int i = 0; i < 4; i++) {
        mux[i].unlock();
    }
}

int main() {
    vector<thread> threadList;
    for(int i = 0; i < 4; i++) {
        threadList.push_back(thread(func, i));
    }
    for(auto val = threadList.begin(); val != threadList.end(); val++) {
        val->join();
    }    
    return 0;
}