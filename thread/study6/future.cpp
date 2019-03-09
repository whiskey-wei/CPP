#include <bits/stdc++.h>

void init(std::promise<int>* promObj) {
    std::cout << "Inside Thread" << std::endl;
    promObj->set_value(35);
}

int main() {
    std::promise<int> promiseObj;
    std::future<int> futureObj = promiseObj.get_future();
    std::thread threadObj(init, &promiseObj);
    std::cout << futureObj.get() << std::endl;
    threadObj.join();
    return 0;
}