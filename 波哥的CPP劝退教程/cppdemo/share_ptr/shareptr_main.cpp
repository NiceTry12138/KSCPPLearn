#include <iostream>
#include <memory>
using namespace std;

class Demo3C
{
private:
    /* data */
public:
    Demo3C(/* args */){cout << "create demo3c" << endl;};
    Demo3C(const Demo3C& other){cout << "copy demo3c" << endl;};
    ~Demo3C(){cout << "release demo3c" << endl;};
};
void demo1(){
    cout << "demo1 begin" << endl;
    Demo3C *a = new Demo3C();
    auto sp_a = shared_ptr<Demo3C>(a);
    auto sp_a2 = make_shared<Demo3C>();
    auto sp_a1 = sp_a;
    sp_a2 = sp_a1;
    cout << "#1: " << sp_a.use_count() << " " << sp_a1.use_count() << endl;
    // auto sp_a2 = make_shared<Demo3C>(sp_a);
    // cout << "#2: " << sp_a.use_count() << "" << sp_a2.use_count() << endl;
    auto sp_a3(sp_a);
    cout << "#3: " << sp_a.use_count() << " " << sp_a1.use_count() << " " << sp_a3.use_count() << endl;
    sp_a3.reset();
    cout << "#4: " << sp_a3.use_count() << " " <<  sp_a1.use_count() << " " << sp_a.use_count() << endl;
    sp_a1 = nullptr;
    cout << "#5: " << sp_a3.use_count() << " " <<  sp_a1.use_count() << " " << sp_a.use_count() << endl;
    sp_a.reset();
    //share_ptr之间如何共享这个计数？
    //reset是如何做到只清空自己的计数，而不影响其他共享指针？
    cout << "demo1 end" << endl;
}

struct Table{
    int val;
};

//unique_ptr version
namespace SHAREPTR{
    class TableReader
    {
    public:
        /* data */
        shared_ptr<Table> item;
    public:
        TableReader(/* args */){};
        ~TableReader(){};
        weak_ptr<Table> reader(string path){
            auto tbl = new Table();
            tbl->val = 1;
            item = shared_ptr<Table>(tbl);
            //recommend: 理由参考<<effect modern c++ 42个条建议>>第21条
            // https://gitee.com/wizardforcel/Effective-Modern-Cpp-Zh/blob/master/SmartPointers/21-Prefer-std-make_unique-and-std-make_shared-to-direct-use-of-new.md
            //item = make_unique<Table>(); 
                             
            //return item; 
            return item;
        }

        void hotfix(){
            if(item.get() == nullptr) return;
            cout << "hotfix before " << item->val << endl;
            item->val = 5;
            cout << "hotfix success " << item->val << endl;
        }

        void releaseTable(){
            if(item.get() == nullptr){
                cout << "has released!" << endl;
                return;
            }
            item.reset();
            return;
        }
    };
}

void demo2(){
    using namespace SHAREPTR;
    TableReader reader;
    auto t = reader.reader("333");
    if(!t.expired()){
        auto tp = t.lock();
        cout << "table data:" << tp->val << " " << tp.use_count()<< endl;
    }
    //t = reader.hotfix(t);
    reader.hotfix();
    if(!t.expired()){
        auto tp = t.lock();
        cout << "table data2:" << tp->val << " " << tp.use_count()<< endl;
    }
    reader.releaseTable();
    if(!t.expired()){
        auto tp = t.lock();
        cout << "table data3:" << tp->val << " " << tp.use_count()<< endl;
    }
}

void demo3_1(shared_ptr<int> ptr){cout << "ref count " << ptr.use_count() << endl;}
void demo3_2(shared_ptr<int>& ptr){cout << "ref count " << ptr.use_count() << endl;}
void demo3(){
    auto t = make_shared<int>(3);
    demo3_1(t);
    demo3_2(t);
}

int main(){
   // demo1();
    demo3();
}