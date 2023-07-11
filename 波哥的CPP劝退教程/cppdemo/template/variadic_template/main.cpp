#include <iostream>
using namespace std;
template<typename T>
auto Max(T&& val){
    return val;
}
template<typename T, typename ... Args>
auto Max(T&& val, Args&&... args){
    return val > Max(forward<Args>(args)...) ? val : Max(forward<Args>(args)...);
}
template<typename ... Args>
auto Max(Args&&... args){
    return Max(forward<Args>(args)...);
}

void demo1(){
    auto a = Max(1, 2, 4, 3);
    cout << a << endl;
}


//demo2
template<typename Ret, typename T, typename... Args> 
Ret CallProxy(T func, Args&&... args);
template<typename Ret, typename... Args> 
Ret CallProxy(Ret(*func)(Args...), Args&&... args){
    //do somthing
    cout << "record call function" << endl;
    return func(forward<Args>(args)...);
}
template<typename Ret, typename ClassType, typename... Args> 
Ret CallProxy(Ret(ClassType::*func)(Args...), ClassType& obj, Args&&... args){
    //do somthing
    cout << "record call class member function" << endl;
    return (obj.*func)(std::forward<Args>(args)...);
}
template<typename Ret, typename ClassType, typename... Args> 
Ret CallProxy(Ret(ClassType::*func)(Args...), ClassType&& obj, Args&&... args) // ClassType&& obj 为什么没有被认为是万能引用，而是一个左值引用版本
{
    //do somthing
    cout << "record call class member function" << endl;
    return (move(obj).*func)(std::forward<Args>(args)...);
}
struct PP {
    int function(int val){cout << "haha: " << val << endl;return 3;}
};
void test_func(int a, int b){
    cout << a << " " << b << endl; 
}
void demo2(){
    CallProxy(&test_func, 1, 2);
    PP tt;
    CallProxy(&PP::function, PP(), 123);
    cout << CallProxy(&PP::function, tt, 123) << endl;
}
int main(){
    demo1();
    demo2();
}