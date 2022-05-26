#include <iostream>
#include "Binder.h"
using namespace std;
class Test
{
public:
	int p1 = 1;
	bool p2 = false;
	std::string p3 = "p33333333";

	void test1(void* params)
	{
		std::cout << "test1" << std::endl;
	}
	static void test2(void* params)
	{
		std::cout << "test2" << std::endl;
	}
};

void test()
{
	Binder<Test> binder;
	binder.bindVar("p1", offsetof(Test, p1));
	binder.bindFunc("test1", &Test::test1);
	binder.bindStaticFunc("test2", Test::test2);

	Test t1;

	int p1 = binder.findVar<int>(&t1, "p1");
	std::cout << p1 << std::endl;

	binder.callFunc(&t1, "test1", nullptr);
	binder.callStaticFunc("test2", nullptr);
}

int main() {
	test();
	return 0;
}