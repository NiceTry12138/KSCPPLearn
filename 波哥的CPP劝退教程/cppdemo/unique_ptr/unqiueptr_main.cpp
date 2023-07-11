#include <iostream>
#include <memory>
using namespace std;


struct Table{
    int val;
    Table(/* args */){cout << "create Table" << endl;};
    Table(const Table& other){cout << "copy Table" << endl;};
    Table(Table&& other){cout << "move Table" << endl;};
    ~Table(){cout << "release Table" << endl;};
};

//auto_ptr version
namespace AUTOPTR{
    class TableReader
    {
    public:
        /* data */
        auto_ptr<Table> item;
    public:
        TableReader(/* args */){};
        ~TableReader(){};
        auto reader(string path){ //auto&？
            auto tbl = new Table();
            item = auto_ptr<Table>(tbl);
            item->val = 1;
            return item;
        }
        void hotfix(string path){
            if(item.get() != nullptr) return;
            cout << "hotfix before " << item->val << endl;
            item->val = 5;
            cout << "hotfix success " << item->val << endl;
        }

        auto hotfix_autoptr(auto_ptr<Table> tbl){
            if(tbl.get() == nullptr) return tbl;
            cout << "hotfix before " << tbl->val << endl;
            tbl->val = 5;
            cout << "hotfix success " << tbl->val << endl;
            return tbl;
        }

        void releaseTable(){
            if(item.get() == nullptr){
                cout << "has released!" << endl;
                return;
            }
            item.reset(nullptr);
        }

        auto releaseTable_autoptr(auto_ptr<Table> tbl){
            if(tbl.get() == nullptr){
                cout << "has released!" << endl;
                return tbl;
            }
            tbl.reset(nullptr);
            return tbl;
        }
    };
};

void demo1(){
    using namespace AUTOPTR;
    TableReader reader;
    auto t = reader.reader("333");
    // cout << "table data:" << reader.item->val << endl;
    cout << "table data:" << t->val << endl;
    // reader.hotfix("3333");
    t = reader.hotfix_autoptr(t);
    cout << "table data2:" << t->val << endl;
    t = reader.releaseTable_autoptr(t);
    //cout << "table data3:" << t->val << endl;
}

//unique_ptr version
namespace UNIQUEPTR{
    class TableReader
    {
    public:
        /* data */
        unique_ptr<Table> item;
    public:
        TableReader(/* args */){};
        ~TableReader(){};
        auto reader(string path){
            auto tbl = new Table();
            tbl->val = 1;
            item = unique_ptr<Table>(tbl);
            //recommend: 理由参考<<effect modern c++ 42个条建议>>第21条
            // https://gitee.com/wizardforcel/Effective-Modern-Cpp-Zh/blob/master/SmartPointers/21-Prefer-std-make_unique-and-std-make_shared-to-direct-use-of-new.md
            //item = make_unique<Table>(); 
                             
            //return item; 
            return move(item);
        }

        auto hotfix(unique_ptr<Table> tbl){
            if(tbl.get() != nullptr) return tbl;
            cout << "hotfix before " << tbl->val << endl;
            tbl->val = 5;
            cout << "hotfix success " << tbl->val << endl;
            return tbl; //RVO
        }

        auto releaseTable(unique_ptr<Table> tbl){
            if(tbl.get() == nullptr){
                cout << "has released!" << endl;
                return tbl;
            }
            tbl.reset(nullptr);
            return tbl;
        }
    };
}

void demo2(){
    using namespace UNIQUEPTR;
    TableReader reader;
    auto t = reader.reader("333");
    cout << "table data:" << t->val << endl;
    cout << "table reader item is null?:" << (t.get() == nullptr) << endl;
    //t = reader.hotfix(t);
    t = reader.hotfix(move(t));
    cout << "table data 2:" << t->val << endl;
    t = reader.releaseTable(move(t));
    //cout << "table data3:" << t->val << endl;
}

//demo3
class Demo3C
{
private:
    /* data */
public:
    Demo3C(/* args */){cout << "create demo3c" << endl;};
    Demo3C(const Demo3C& other){cout << "copy demo3c" << endl;};
    ~Demo3C(){cout << "release demo3c" << endl;};
};
Demo3C *a = new Demo3C();
//智能指针用不好，同样会内存泄漏或者访问野指针哟。
void demo3_1(){
    //原始指针
    //auto sp_a = unique_ptr<Demo3C>(a);
    //auto sp_a = make_unique<Demo3C>(a);
    auto sp_a = make_unique<Demo3C>(*a); //raw pointer 不能使用这种方式去创建智能指针
    sp_a.reset();
    //cout << "a is null?: " << (a == nullptr) << endl;
    delete a;
    // cout << "11" << endl;
    // auto b = sp_a.release();
    // cout << "sp_a is null?:" << (sp_a.get() == nullptr) << " a is null?: " << (a == nullptr) << endl;
    // auto sp_b = move(sp_a);
    // sp_b.reset();
    // cout << "sp_b is null?:" << (sp_b.get() == nullptr) << ", a is null?: " << (a == nullptr) << endl;
    
    cout << "function end" << endl;
}

void demo3_2(){
    auto sp_a = make_unique<Demo3C>();
}

//用一个原始指针初始化多个智能指针是一件非常愚蠢的行为
void demo3_3(){
    Demo3C *a = new Demo3C();
    auto sp_a = unique_ptr<Demo3C>(a); 
    auto sp1_a = unique_ptr<Demo3C>(a); 
}


int main(){
    // demo1();
    //demo2();

    // demo3
    // demo3_1();
    //delete a;
    //demo3_2();
    demo3_3();
    return 0;
}