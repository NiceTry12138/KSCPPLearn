#include <iostream>
using namespace std;

template<typename T> T pi = T(3.1415926); // 这个constexpr有和没有差别还是很大的。
template<class T>
constexpr T circular_area(T r)
{
    return pi<T> * r * r;
}
void demo1(){
    auto a = pi<int> * 5;
    auto b = pi<float> * 10.0f;
    auto c = pi<double> * 10.0;
    // cout << a << " " << b << " " << c << endl;

    // auto f = circular_area(10.0f);
}


struct Radian{};
template <typename T> constexpr T pai = T{}; 
template <> float pai<float> = 3.1415926;
template <> int pai<Radian> = 180;
void demo2(){
    cout << pai<Radian> * 3 << endl;
}

template <int N> const int ctSquare = N*N;  
void demo3(){
    cout << ctSquare<7><< endl;
}


int main(){
    demo1();
    pi<int> = 180;
    demo2();
    //demo3();
    return 0;
}