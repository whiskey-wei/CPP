#include <bits/stdc++.h>
using namespace std;

class Base {
public:
    virtual void fun() {
        cout << "Base" << endl;
    }
};
class Son1:public Base {
public:
    void fun() {
        cout << "Son1" << endl;
    }
};
class Son2:public Base {
public:
    void fun() {
        cout << "Son2" << endl;
    }
};
int main() {
    Base *base;
    Son1 son1;
    Son2 son2;
    base = &son1;
    base->fun();
    base = &son2;
    base->fun();
    return 0;
}