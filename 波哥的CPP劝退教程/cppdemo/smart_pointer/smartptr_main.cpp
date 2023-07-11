#include <iostream>
#include <map>
using namespace std;

struct Test{
    int a;
    float b;
    Test(int a, float b):a(a), b(b){}
};

void demo1(){
    int *a = new int(10);
    int *b = a;
    delete b;
    //delete a;  //#1
    b = nullptr;
    a = nullptr;
    *b = 11;    //#2
    cout << *a << endl;

    // b = nullptr;
    // cout << (a == nullptr) << endl;
    
    // auto c = new Test(1, 0.1f);
    // *b = 12;
    // cout << c->a << endl;
    // cout << b << " " << &(c->a) << endl;
}

//demo2
namespace RAWPTR
{
    struct Table{
        int val;
    };

    class TableReader
    {
    public:
        /* data */
        Table *item = nullptr;
    public:
        TableReader(/* args */){};
        ~TableReader(){if(item)delete item;}
        Table* reader(string path){
            if(item != nullptr){
                delete item;
                item = nullptr;
            }
            item = new Table();
            item->val = 1;
            cout << item << endl;
            return item;
        }
        void hotfix(string path){
            if(item == nullptr) return;
            cout << "hotfix before " << item->val << endl;
            item->val = 5;
            cout << "hotfix success " << item->val << endl;
        }
        void releaseTable(){
            if(item == nullptr) return;
            delete item;
            item = nullptr;
        }
    };
};
void demo2(){
    using namespace RAWPTR;
    TableReader reader;
    auto t = reader.reader("333");
    cout << t << endl;
    // delete t;
    // t = nullptr;
    // 
    // cout << a << endl;
    //reader.releaseTable();
    cout << reader.item->val << endl;
    t = nullptr;
    reader.hotfix("3333");
    int* a = new int (11);
    cout << reader.item->val << endl;
}


int main(){
    // demo1();
    demo2();
    return 0;
}
