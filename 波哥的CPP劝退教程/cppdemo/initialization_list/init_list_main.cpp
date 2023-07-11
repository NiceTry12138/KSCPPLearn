#include <iostream>
#include <vector>
using namespace std;

//demo1
int f(vector<int> b){
    return 3;
}
int f(int) {return 6;};
void demo1(){
    vector<int> aa(1);
    cout << f(3) << endl;
}

class A
{
private:
    /* data */
    int _val;
public:
    A(int v1): _val(v1){};
    ~A(){};
};
//demo2 括号的二义性
A a(int b){cout << "function A" << endl;};
void demo2(){
    A a(1;
}

//demo3 类型变窄
//A a(1.3);
// A a = {1.3};



//demo 4{} != ()
void demo4(){
    char b = 'b';
    string str1(b, 'a');
    string str2{b, 'a'};
    cout << (str1 == str2) << endl;
    cout << "str1:" << str1 << endl;
    cout << "str2:" << str2 << endl;
}


int main(){
    demo1();
    demo2();
    // demo3();
    demo4();
    return 0;
}