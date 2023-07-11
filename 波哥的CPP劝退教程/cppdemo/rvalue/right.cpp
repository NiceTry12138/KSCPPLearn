#include <iostream>
#include <vector>
#include <memory>
using namespace std;

int get_int(){
    int a = 3;
    return a;
}

void demo1(){
    int a = 11;
    int &a_ref = a;
    auto& c = a_ref;
    cout << "a address:" << &a << ", a_ref address: "<< &a_ref << endl;

    cout << is_lvalue_reference<decltype(a)>::value << endl;
    cout << is_lvalue_reference<decltype(a_ref)>::value << endl;
    cout << is_lvalue_reference<decltype(get_int())>::value << endl;
}


//这里其实用到了引用折叠
template<typename T>
bool isLvalue(T&&) {
    return std::is_lvalue_reference<T>::value;
}
void demo2(){
    int &&d = get_int();
    int a1 =1, a2= 3;
    cout << "address:" << &d << ", value: "<< d << endl;
    cout << is_lvalue_reference<decltype(d)>::value << endl;
    cout << isLvalue(a2) << endl;
    cout << isLvalue(d) << endl;
    cout << isLvalue(a1+a2) << endl;
    cout << isLvalue(move(a1)) << endl;
    auto x = move(a1);
    cout << isLvalue(x) << endl;
}


int main(){
    demo1();
    demo2();
    return 0;
}