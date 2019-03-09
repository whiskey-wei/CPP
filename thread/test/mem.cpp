#include <iostream>
using namespace std;

class myClass {
public:
 myClass()     {
            cout << "Create a myClass with Constructors" << endl;
        }
        ~myClass()  {
            cout << "Delete a myClass with Destructors" << endl;
        }
        void test() {
            cout << "i am test" << endl;
        }
 };

 int main() {
    myClass* p  = (myClass*)malloc(sizeof(myClass));
    p->test();
    delete p ;
    p  = new myClass[3];
    delete[] p ;
    return 0;
}