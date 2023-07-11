#include <iostream>
using namespace std;

void sum(int &a, int &b);
void sum(int&& a, int && b);
void sum(int& a, int&& b);
void sum(int&& a, int& b);

template<typename T>
void sum(T&& a, T&& b);


// template<typename T>
// void function_test(T& param){
//     cout << "func 1" << endl;
// }
template<typename T>
void function_test(T&& param){
    cout << "is param lvalue ref?:" << is_lvalue_reference<decltype(param)>::value << endl;
    cout << "func 2" << endl;
}

void demo1(){
    int a = 1;
    int& b = a;
    int&& c = 3;
    function_test(a);
    function_test(b);
    function_test(move(a));
    // function_test(c);

    auto&& d = a;
    auto&& e = b;
    auto&& f = c;
    auto&& g = 13;
    cout << "is d lvalue ref?:" << is_lvalue_reference<decltype(d)>::value << endl;
    // cout << "is e lvalue ref?:" << is_lvalue_reference<decltype(e)>::value << endl;
    // cout << "is f lvalue ref?:" << is_lvalue_reference<decltype(f)>::value << endl;
    // cout << "is g lvalue ref?:" << is_lvalue_reference<decltype(g)>::value << endl;
}

//forward
struct Number {
    Number(int&& n){cout << "move init" << endl;}
    Number(const int& n){cout << "copy init" << endl;}
};


void demo2(int&& val){
    int a = 3;
    Number num3(move(a));
    Number num1(val);
    Number num2(forward<int>(val));
}



template<typename Type>
struct func_op
{
  template<typename T> void operator()(T&& t);
};

template<>
struct func_op<Number>
{
  template<typename T> void operator()(T&& t)
  {
    cout << "number function: " << is_lvalue_reference<decltype(t)>::value << endl;
  }
};

template <typename T>
void func(T&& t) 
{
  func_op<std::decay_t<T>> op;
  return op(forward<T>(t));
}


void demo3(){
    Number a = 4;
    func(a);
    func(move(a));
    func(5);
}


int main(){
   // demo1();
    // demo2(3);
    demo3();
    return 0;
}