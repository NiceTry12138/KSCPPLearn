#include <iostream>
#include <vector>
using namespace std;


class T {
    public:
    const int a{3};
};

int main(){
    //C++98
    //for(init; condition; operator)
    int a[4] = {1,2,3,4};
    for(int i = 0; i < sizeof(a)/sizeof(int); i++){cout << i << endl;}
    vector<int> vec = {11, 22, 33, 44, 55};
    for(auto iter = vec.begin(); iter != vec.end(); iter++){cout << *iter << endl;}
    

    //C++11 for([init];range_dcl:range_expr)
    cout << "##############"<<endl;
    for(auto x: a)
        cout << x << endl;
    int sum;
    for(sum = 0; auto& x: a){
        sum += x;
    }
    cout << sum << endl;
    // for(int i{0}; auto& x: a){
    //     x = vec.at(i);
    //     i++;
    // }


    // for(auto&& x: a)
    //     cout << x << endl;
    ////
    for(auto& x: vec){
        if(x == 22) x = 23;
    }
    for(auto x: vec)
        cout << x << endl;

    
    ////////////
    vector<bool> bVec = {true, false, true};
    for(auto x: bVec){
        x = false;
    }
    
    for(auto&& x: bVec)
        cout << x << endl;
    return 0;
}

template<typename T>
T getSum(vector<T> vec){
    
}