#include <bits/stdc++.h>

using namespace std;

class Wallet {
    int mMoney;
    mutex mux;
public:
    Wallet() :mMoney(0) { }
    int getMoney() {
        return mMoney;
    }
    void addMoney(int money) {
        for(int i = 0; i < money; i++) {
            mMoney++;
        }
    }
    void addMoneyMutex(int money) {
        mux.lock();
        for(int i = 0; i < money; i++) {
            mMoney++;
        }
        mux.unlock();
    }

    //std::lock_guard是一个template class，
    //它为mutex实现RALL，它将mutex包裹在其对象内，
    //并将附加的mutex锁定在其构造函数中，当其析构函
    //数被调用时，它将释放互斥体。
    void addMoneylockGuard(int money) {
        lock_guard<mutex> lock_Guard(mux);
        for(int i = 0; i < money; i++) {
            mMoney++;
        }
    }
};

int ThreadWallet() {
    vector<thread> threads;
    Wallet walletObj;
    for (int i = 0; i < 5; i++) {
        threads.push_back(thread{&Wallet::addMoney, &walletObj,1000});
    }
    for (int i = 0; i < 5; i++) {
        threads.at(i).join();
    }
    return walletObj.getMoney();
}

int ThreadWalletMutex() {
    vector<thread> threads;
    Wallet walletObj;
    for (int i = 0; i < 5; i++) {
        threads.push_back(thread{&Wallet::addMoneyMutex, &walletObj,1000});
    }
    for (int i = 0; i < 5; i++) {
        threads.at(i).join();
    }
    return walletObj.getMoney();
}

int ThreadWalletlockGuard() {
    vector<thread> threads;
    Wallet walletObj;
    for (int i = 0; i < 5; i++) {
        threads.push_back(thread{&Wallet::addMoneylockGuard, &walletObj,1000});
    }
    for (int i = 0; i < 5; i++) {
        threads.at(i).join();
    }
    return walletObj.getMoney();
}

int main() {
    int val = 0;
    int err = 0;
    for (int k = 0; k < 1000; k++) {
        if ((val = ThreadWallet()) != 5000) {
            cout << "Error at count = " << k << "Money is " << val << endl;
            err++;
        }
    }
    cout << "error num is: " << err << endl;


    err = 0;
    for (int k = 0; k < 1000; k++) {
        if ((val = ThreadWalletMutex()) != 5000) {
            cout << "Error at count = " << k << "Money is " << val << endl;
            err++;
        }
    }
    if (err == 0) {
        cout << "mutex no error" << endl;
    }


    err = 0;
    for (int k = 0; k < 1000; k++) {
        if ((val = ThreadWalletlockGuard()) != 5000) {
            cout << "Error at count = " << k << "Money is " << val << endl;
            err++;
        }
    }
    if (err == 0) {
        cout << "lock_guard no error" << endl;
    }
    return 0;
}