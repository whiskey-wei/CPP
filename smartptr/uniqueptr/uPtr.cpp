#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct DefaultDeleter
{
    /* data */
    void operator()(T *p) {
        if (p) {
            delete p;
            p = nullptr;
        }
    }
};

template<typename T, typename Deleter = DefaultDeleter<T>>
class uPtr
{
private:
    /* data */
    T *m_p;
    Deleter m_deleter;
    void del()
    uPtr(const uPtr &);
    uPtr &operator=(const uPtr &);
public:
    uPtr(T *p = nullptr):m_p(p) {}
};

