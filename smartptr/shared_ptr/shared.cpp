#include <memory>
#include <iostream>

class Myclass {
public:
    int x;
    int y;
    Myclass(int a = 0, int b = 0):x(a),y(b) {
        std::cout << "gouzao" << x << y << std::endl;
    }
    ~Myclass() {
        std::cout << "xigou" << x << y << std::endl;
    }
};

int main() {
    /*std::shared_ptr<int> p1 = std::make_shared<int>();
    *p1 = 78;
    std::cout << "p1 = " << *p1 << std::endl;
    std::cout << "p1 Reference count = " << p1.use_count() << std::endl;

    std::shared_ptr<int> p2(p1);
    std::cout << "p2 = " << *p2 << std::endl;
    std::cout << "p1 Reference count = " << p1.use_count() << std::endl;
    std::cout << "p2 Reference count = " << p2.use_count() << std::endl;

    if (p1 == p2) {
        std::cout << "p1 == p2" << std::endl;
    }

    std::cout << "Reset p1" << std::endl;
    p1.reset();
    std::cout << "p1 Reference count = " << p1.use_count() << std::endl;

    p1.reset(new int(11));
    std::cout << "p1 Reference Count = " << p1.use_count() << std::endl;

    p1 = nullptr; 
    std::cout << "p1 Reference Count = " << p1.use_count() << std::endl;

    if (!p1) {
        std::cout << "p1 is NULL" << std::endl;
    }

    std::cout << "\n-------------------\n" << std::endl;

    Myclass* p = new Myclass(2, 3);

    p = new Myclass(4,5);//内存泄漏

    delete p;

    std::cout << "\n--------------------\n" << std::endl;*/

    std::shared_ptr<Myclass> p1(new Myclass(1, 1));
    std::shared_ptr<Myclass> p2(new Myclass(2, 2));
    std::shared_ptr<Myclass> p3(p2);
    std::cout << "p1:" << p1.use_count() << std::endl;
    std::cout << "p2:" << p2.use_count() << std::endl;
    p1.reset(p2.get());
    p3.reset();
    std::cout << "after reset" << std::endl;
    //std::cout << "p3:" << p3->x << p3->y << std::endl;
    std::cout << "p1:" << p1.use_count() << std::endl;
    std::cout << "p2:" << p2.use_count() << std::endl;

    return 0;

}