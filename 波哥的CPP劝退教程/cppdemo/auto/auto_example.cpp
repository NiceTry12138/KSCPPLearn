#include <typeinfo>
#include <iostream>
using namespace std;
const int x = 3;

int auto_int(){
    auto a = x;
    cout << typeid(a).name() << endl;
    return a;
}


void auto_ref(){
    int a =5;
    int &b = a;
    auto c = b;
    c = 10;
    cout << "ref b:" << b << endl;
    b = 11;
    cout << "a:" << a << endl;
    

    auto &&d = a;
    auto &&f = b;
    auto &&g = move(a);
}

void auto_const(){
    //推倒舍弃const
    const auto n = x;  //n 为 const int ，auto 被推导为 int
    auto f = n;      //f 为 const int，auto 被推导为 int（const 属性被抛弃）
    f = 4;

    const auto &r1 = x;  //r1 为 const int& 类型，auto 被推导为 int
    auto &r2 = r1;  //r1 为 const int& 类型，auto 被推导为 const int 类型
   // r2 = 6;

    // int no_const_n = x;
    // no_const_n = 6;

    // int &noconst_ref_r1 = x;
}

auto auto_return(int input){
    switch (input)
    {
    case 1:
        return 1;
        /* code */
        break;
    case 2:
        //return 2.0;
        break;
    default:
        return 3;
        break;
    }
}

class AutoClassTest
{
private:
    static auto const cc = x;
    // static auto t = 4;
    // auto y = x;
    /* data */
public:
    AutoClassTest() { cout << AutoClassTest::cc << endl;}
    ~AutoClassTest() {}
};


void auto_array(){
    int a[3] = {1,2,3};
    a[0];
    auto b = a; // auto == int*
    auto c = {1,2,3}; // auto == initializer_list c++ 11
   auto d[3]= {1,2,3};
}


int main(){    
    // auto_int();
    // auto res = auto_float();
    // cout << "auto_float:" << typeid(res).name() << endl;
    // auto_ref();
    // auto_const();
    // auto_return(1);
    auto_array();
    return 0;
}