#include <iostream>
#include <tuple>
#include <array>
#include <vector>
using namespace std;

// const int n = 3;
// int b1[n] = {1,2,3};

auto a = make_tuple(2002, "xxx", 2004, true);
    //获取tuple的长度
auto size = tuple_size<decltype(a)>::value; //编译阶段
int b[tuple_size<decltype(a)>::value]={1,2,3};

void demo1(){
    auto a = make_tuple(2002, "xxx", 2004, true);
    //获取tuple的长度
    auto size = tuple_size<decltype(a)>::value; //编译阶段
    int b[tuple_size<decltype(a)>::value]={1,2,3};
    //获取type中某个元素和元素的类型
    auto a1 = get<0>(a);
    typedef tuple_element<0, decltype(a)>::type a1_type;
    //解包
    int year;
    string name;
    bool flag;
    tie(year,name,ignore,flag) = a;
    auto [param1, param2, param3, param4] = a;
    cout << year << " " << name << " " << flag << endl;
    cout << param1 << " " << param2 << " " << param3 << endl;
}

//demo2 gcc能通过c的非标准扩展 VLA特性编译通过, 或者打开-Wvla开关，建议放在msvc编译环境测试下面代码
int demo2_1(int n){
    int a[n];
    a[0] = 1;
    cout << a[0] << endl;
}

int demo2_2(vector<int> vec){
    const int len = vec.size();
    int a[len];
    a[0] = 1;
    cout << a[0] << endl;
}

template<typename... Args>
void demo2_3(tuple<Args...> t){
    auto size = tuple_size<decltype(t)>::value; //编译阶段
    cout << size << endl;
    int a[size];
    return;
}

void demo2(){
    demo2_3(make_tuple(1, 2, "hhl"));
}


int main(){
    //demo1();
    demo2();
    return 0;
}


