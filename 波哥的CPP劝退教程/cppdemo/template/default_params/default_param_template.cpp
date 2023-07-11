#include <iostream>
#include <array>
using namespace std;

//C98/03
template<typename T = int, int N = 10>
class TemplateClass {
private:
    array<T,N> _array;
public:
    TemplateClass() {}
    const auto getArray() { return _array;}
};
void demo1(){
    TemplateClass<int> a;
    TemplateClass<int, 20> b;
    cout << "a size: " << a.getArray().size() << endl;
    cout << "a size: " << b.getArray().size() << endl;
}

//c++ 11
struct A{
};

struct B
{
};
template <typename T = A, typename U = double>
void func(T val1 = B(), U val2 = 0)
{
}
void demo2() {
    //func();
    func(B());
}



int main(){
    demo1();
    demo2();
}

