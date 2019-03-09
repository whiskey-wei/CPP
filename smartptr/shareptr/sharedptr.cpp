#include <iostream>
#include <string>
using namespace std;

template<typename T>
class SharedPtr
{
private:
    /* data */
    T *_ptr;
    int *_refcount;
public:
    SharedPtr():_ptr((T*)0), _refcount(0) {

    }
    SharedPtr(T *obj):_ptr(obj), _refcount(new int(1)) {
        cout << "create object:" << *_ptr << "\trefcount = " << *_refcount << endl;
    } 
    SharedPtr(SharedPtr &other) : _ptr(other._ptr), _refcount(&(++*other._refcount)) {
        cout<<"copy constructor : " << *_ptr <<"\trefCount = " << *_refcount<<endl;
    }
    ~SharedPtr() {
        if (_ptr && --*_refcount == 0) {
            cout<<*_ptr<<"\trefCount = 0. delete the _ptr:"<<*_ptr<<endl;
            delete _ptr;
            delete _refcount;
        }
    }
    SharedPtr &operator=(SharedPtr &other) {
        if(this == &other) {
            return *this;
        }
        ++*other._refcount;
        if(--*_refcount == 0) {
            cout<<"in function operator = . delete "<<*_ptr<<endl;
            delete _ptr;
            delete _refcount;
        }
        _ptr = other._ptr;
        _refcount = other._refcount;
        cout<<"in function operator = . "<<*_ptr<<"\t_refCount = "<<*_refcount<<endl;
        return *this;
    }

    T *operator ->() {
        if (_refcount == 0) {
            return 0;
        }
        return _ptr;
    }

    T &operator *() {
        if (_refcount == 0) {
            return (T*)0;
        }
        return *_ptr;
    }
};

int main() {
    SharedPtr<string> p1(new string("abc"));
    SharedPtr<string> p2(p1);
    SharedPtr<string> p3(new string("hao"));
    p3 = p2;
    return 0;
}