#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct Element{
    int val= 3;
};

struct Tiramisu {
    int length;
    Element* compositions = nullptr;
    Tiramisu(int val):length(val), compositions(new Element[val]){cout << "init construct" << endl;};
    ~Tiramisu() {
        cout << "release cake" << endl;
        length = 0;
        if(compositions) delete[]compositions;
        compositions = nullptr;
    }
    Tiramisu(const Tiramisu& other): length(other.length), compositions(new Element[length]) {
        cout << "copy construct" << endl;
        compositions = new Element[other.length];
        copy(other.compositions, other.compositions + length, compositions);
    }
    Tiramisu& operator=(const Tiramisu& other){
        cout << "copy assign" << endl;
        if (this != &other)
        {
            delete[] compositions;
            length = other.length;
            compositions = new Element[length];
            copy(other.compositions, other.compositions + length, compositions);
        }
        return *this;
    }

    // //move
    Tiramisu(Tiramisu&& other): length(other.length), compositions(other.compositions) {
        cout << "move construct" << endl;
        other.length = 0;
        other.compositions = nullptr;
    }
    Tiramisu& operator=(Tiramisu&& other){
        cout << "move assign" << endl;
        if (this != &other)
        {
            length = other.length;
            compositions = other.compositions;
            other.length = 0;
            other.compositions = nullptr;
        }
        return *this;
    }
};

vector<Tiramisu> cakes;
void demo1(){
    cakes.reserve(10);

    Tiramisu a1(1);
    Tiramisu a2(2);
    // cakes.push_back(a1);
    // cakes.push_back(a2);
    //cakes.push_back(Tiramisu(1));
    //cakes.push_back(Tiramisu(2));
    //2个右值其实在pushback之后就会被销毁，简直浪费，我们又没办法废物利用，延长里面配料的寿命呢？
}

void demo2(){

    Tiramisu a1(1);
    Tiramisu a2(2);
    cakes.reserve(10);
    cakes.push_back(a1);
    cakes.push_back(a2);

    cakes.push_back(move(a1));
    cakes.push_back(move(a2));

    //cakes.push_back(Tiramisu(1));
    //cakes.push_back(Tiramisu(2));
}


//vector<unique_ptr<T>> attention
vector<unique_ptr<Tiramisu>> unique_cakes;
void demo3(){
    unique_cakes.push_back(make_unique<Tiramisu>(1));
    unique_cakes.push_back(make_unique<Tiramisu>(2));
    
    auto&& cake = unique_cakes.at(0);
    //auto cake = move(unique_cakes.at(0));
    cout << cake.get()->length << endl;
    cout << unique_cakes.at(0).get()->length << endl;

    for(auto&& iter: unique_cakes){
        cout << iter.get()->length << endl;
    }
    cout << unique_cakes.at(0).get()->length << endl;
}



int main(){
    //demo1();
    //cout <<"demo1 end" << endl; //每一次push都会发生一次拷贝,
    demo2();
    //cout <<"demo2 end" << endl; //每次一次push只是新瓶装旧酒
    //demo3();
    return 0;
}