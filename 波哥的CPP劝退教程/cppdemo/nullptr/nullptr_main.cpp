#include <iostream>
using namespace std;
void doSomething(int)
{
    std::cout<<"int version";
}
void doSomething(char *)
{
   std::cout<<"char* version";
}

void demo1(){
    // doSomething(NULL);
    doSomething(0);
    doSomething(nullptr);
}

class A
{
private:
    /* data */
public:
    A(/* args */){};
    ~A(){};
    void doSomething(){};
};



// demo2 兼容性
// #define NULL ((void*)0)
// #define NULL 0
void demo2(){
    string * str = NULL;         //Case 1
    //void(A::*p)() = &A::doSomething;
    //if(p != NULL){};
    //if(p != nullptr){};
}


//demo3 what is null_ptr
void demo3(){
    nullptr_t new_ptr_1(0);
    cout << "ans:" << (nullptr == new_ptr_1) << endl;
}

int *a = nullptr;
struct C{
    int *t = nullptr;
    void(*fp)() = nullptr;
    void func(){};
};
using type = decltype(&C::func);


int main()
{
    demo3();
    return 0;
}