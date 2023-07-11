#include <iostream>
#include "Test1.h"
#include "Test2.h"
#include "DeleteTest.h"
using namespace std;
int demo1(){
    // Demo::add(1,2,3);
    // Demo::add(1, false);
    // Demo::add(1, 1.3f);
}

void demo2(){
    DeleteA a;
    HelloWorld b;
    Proxy p;
    p.dispatch(&a);
    p.dispatch(&b);
}
 
//demo3
class Demo3
{
    friend void copy(const Demo3& src, Demo3& to);
private:
    /* data */
    Demo3& operator =(const Demo3& other){
        this->_val = other._val;
        return *this;
    }
public:
    Demo3() {}
    Demo3(int val):_val(val){};
    ~Demo3() {};
    Demo3(const Demo3& other):_val(other._val){}
    Demo3& operator =(const Demo3& other) = delete;
    int _val = 1;
};
void copy(const Demo3& src, Demo3& to){
    to = src;
}
void demo3(){
    Demo3 d1(2);
    Demo3 d2;
    //d2 = d1;
    copy(d1, d2);
    cout << "val: " << d2._val << endl;
}

int main(){
    demo2();
    // demo3();
    return 0;
}