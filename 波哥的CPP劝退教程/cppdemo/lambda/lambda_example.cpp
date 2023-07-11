#include <iostream>
#include <functional>
using namespace std;

void output(int x){
    cout << x << endl;
}

//demo2
void lambda_func_ptr_example(){
    using funcptr = void(*)(int);
    funcptr func1 = [](int x){};
    //funcptr func2 = [=](int x){};
}

int main(){    
    //demo1
    int a = 3;
    // auto f1 = [=](){a = 2;};
    // f1();

    auto f2 = [=]()mutable{a = 2;};
    f2();
    cout << "a: " << a << endl;
    int b =3;
    auto f3 = [&b]()mutable{b = 1;};
    f3();
    cout << "b:" << b << endl;
    //auto f4 = [](int &x){x = 1;};
    //cout << "b: " << b << endl;
    
    //auto f6 = [](int& x){cout << "f6:" << x << endl;};


    //demo3        
    std::function<void()> funcList[3];
    for(int i = 0; i < 3; i ++){
        //  cout << &i << endl;
        //bind
        //funcList[i] = bind([&](int x){output(x+i);}, 1);
        //funcList[i] = bind([=](int x){output(x+i);}, 1);
        //funcList[i] = bind([](int x, int val){output(x+val);}, 1, i);
        //funcList[i] = bind([](int x, int& val){output(x+val);}, 1, i);

        //funcList[i] = [=](){output(i);};
        //funcList[i] = [&](){output(i);};

        int *p = new int(i);
        cout << p <<endl;
        funcList[i] = [&](){
            output(*p);
        };
        delete p;
    }
    int *pp = new int(66);
    cout << pp << endl;
    funcList[0]();
    funcList[1]();
    funcList[2]();

    return 0;
}