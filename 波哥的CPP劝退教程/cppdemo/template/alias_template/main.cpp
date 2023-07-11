#include <iostream>
#include <map>
using namespace std;

template<typename T>
struct Allocator{
    using type = T;
};
template<typename T, typename All>
class Vector{
};
void demo1()
{
    Vector<int, Allocator<int>> v1;
    Vector<int, Allocator<int>> v2;
    //我们好像可以用类型别名简化代码
    using VecI = Vector<int, Allocator<int>>;
    VecI v3; 
    //但是如果我要定义个float的Vec咋办？再来一遍
    using VecF = Vector<float, Allocator<float>>;
    VecF v4;
}

template<typename T>
using Vec = Vector<T, Allocator<T>>;
void demo2()
{
    Vec<int> v1;
    Vec<float> v2;
}

template<typename ValueType>
using StrMap = map<string, ValueType>;
StrMap<int> map1;

int main(){
    map1.insert(std::make_pair("33", 3));
}

