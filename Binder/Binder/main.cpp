#include <iostream>
#include "Binder.h"
#include "Binder1.h"
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

std::string printBool(bool val) {
	return val ? std::string("true") : std::string("false");
}

void test()
{
	Binder<Test> binder;
	binder.bindVar("p1", offsetof_binder(Test, p1));
	binder.bindFunc("test1", &Test::test1);
	binder.bindStaticFunc("test2", Test::test2);

	Test t1;

	int p1 = binder.findVar<int>(&t1, "p1");
	std::cout << p1 << std::endl;

	binder.callFunc(&t1, "test1", nullptr);
	binder.callStaticFunc("test2", nullptr);
}

void test1() {
	Binder1 binder;
	
	Test t1;
	t1.p1 = 2;

	binder.bindVar("p1", offsetof(Test, p1));
	binder.bindVar("p2", offsetof(Test, p2));
	binder.bindVar("p3", offsetof(Test, p3));
	int val1 = binder.findVar<Test, int>(&t1, "p1");
	bool val2 = binder.findVar<Test, bool>(&t1, "p2");
	std::string val3 = binder.findVar<Test, std::string>(&t1, "p3");
	std::cout << "p1 = "  << val1 << " p2 = " << printBool(val2) << " p3 = " << val3 << std::endl;
}

int main() {
	test1();
	return 0;
}