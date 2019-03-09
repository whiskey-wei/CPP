#include <new>
#include <iostream>
using namespace std;

struct Myclass
{
    /* data */
    int a = 2,b = 3;
};

int main() {
    char x[sizeof(Myclass)];
    Myclass *fpr = new(&x[0])Myclass;
    fpr->a = 3;
    fpr->b = 5;
    cout << fpr << endl;
    cout << &x[0] << endl;
    return 0;
}