#include <bits/stdc++.h>
using namespace std;

struct myClass {
public:
    virtual void fun() {};
};
int main() {
    cout << sizeof(myClass) << endl;
    return 0;
}