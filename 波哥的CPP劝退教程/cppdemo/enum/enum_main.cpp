#include <iostream>
using namespace std;

void print(int val){cout << "val: " << val << endl;}

void demo1(){
    enum Test {t1 = 1, t2 = 2, t3 = 3};
    print(1);
    print(t2);
    
    enum class Test1 {t1 = 1, t2 = 2, t3 = 3};
    // print(Test1::t1);
    print((int)Test1::t1);
}

void demo2() {
    //enum Test {t1 = 1, t2, t3};
    // enum Test1 {t1 = 3, t2, t3};

    enum class Test1 {t1 = 1, t2, t3};
    enum class Test2 {t1 = 5, t2, t3};
    // print((int)Test1::t2);
    // print((int)Test2::t2);
}

void demo3(){
    enum class Test:u_char {t1 = 1,t2, t3};
    enum class Test1 {t1 = 1,t2, t3};
    enum class Test2:bool {t1 = true, t2 = false};
    cout << "Test size: " << sizeof(Test::t1) << endl;
    cout << "Test1 size: " << sizeof(Test1::t1) << endl;
    cout << "Test2 size: " << sizeof(Test2::t2) << endl;
}

int main(){
    demo1();
    demo2();
    demo3();
}