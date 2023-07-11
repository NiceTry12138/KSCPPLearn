#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> vec = { 1,3,2,5,7,6 };
    vector<string> strings = {"aa", "dd", "cc"};
    cout << "xxxx" << endl;
    auto cmp = [](auto x, auto y){return x > y;};
    sort(vec.begin(), vec.end(), cmp);
    sort(strings.begin(), strings.end(), cmp);
    // for(const auto& x: vec) cout << x << " ";
    // cout << endl;
    //for(const auto& x: strings) cout << x << " ";
    //cout << endl;
    return 0;
} 
