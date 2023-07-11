#include <iostream>
#include <utility>
using namespace std;

int func(){
    return 3;
}

int func1(){return 3;}
int e(){}
void decltype_init(){
    auto a = 3;
    decltype(2) b;
    decltype(3) c = 3.1415;
    decltype(func()) d;
    //decltype(func) e; //这是一个函数名为e, 无参，返回值为int
    decltype(func)* f; //这是一个函数指针
    // f = func1;
    //f = []()->int{return 2;};
    cout << e() << endl;
    // cout << "func:" << e << " " << f() << " " << d << endl;
}

void decltype_ref() {
    int a = 4;
    int &ref_a = a;
    decltype(ref_a) b = a;
    b = 6;
    cout << "ref_test: " << a << " " << ref_a << " " << b << endl;
}

void decltype_const() {
    const int a = 3;
    decltype(a) b = 4;
    // b = 5;
}

// void func_r(int &a){
//     cout << "55" << endl;
// }

// void func_r(int &&a){
//     cout << "66" << endl;
// }


void decltype_rule() {
    int a = 3, b =4;
    decltype(a) a1;
    decltype((a)) a2 = a;

    decltype(1 + 1) b1;
    decltype((1 + 1))b2;

    int &&d_rr = 2;
    decltype(d_rr) d1 = 3;
    decltype((d_rr)) d = a;

    decltype(a++) d3 = 10;
    decltype(++a) d4 = a;
    //decltype(move(a)) d5;

    // decltype(true?a:b) dx1;
    // decltype(true?a:(a+1)) dx2;

    int c[3] = {1,3,5};
    int array[2] = {1,2};
    decltype(c) t;
    auto t1 = c;
    //t = array;
    t1 = array;
}

int main() {
    decltype_init();
    // decltype_ref();
    // decltype_const();
    // decltype_rule();
    return 0 ;
}