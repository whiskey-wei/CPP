#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

mutex mx;
condition_variable cond;
atomic<int> flag(0);

void func() {
    unique_lock<mutex> lk(mx);
    printf("hello\n");
    flag++;
    while(flag != 4){
        /* code */
        cond.wait(lk);
    }
    printf("world\n");
    cond.notify_all();
}

int main() {
    vector<thread> job;
    for (int i = 0; i < 4; i++) {
        job.push_back(thread(func));
    }
    for (auto i = job.begin(); i != job.end(); i++) {
        i->join();
    }
    return 0;
}