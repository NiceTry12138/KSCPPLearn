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

struct A {
	void func() {
		std::cout << "void A::func()" << std::endl;
	}
	int a;
	double d;
	char c;
	bool b;
	float f;
	std::string str;
};

int main() {
	Binder<A> bd;
	bd.bindVar("a", offsetof(A, a));
	bd.bindVar("b", offsetof(A, b));
	bd.bindVar("c", offsetof(A, c));
	bd.bindVar("d", offsetof(A, d));
	bd.bindVar("f", offsetof(A, f));
	bd.bindVar("str", offsetof(A, str));

	A a;
	a.a = 1;
	std::cout << bd.findVar<int>(&a, "a") << std::endl;
	return 0;
}