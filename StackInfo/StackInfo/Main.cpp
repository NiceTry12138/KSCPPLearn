#include <iostream>
#include <string>
#include "StackInfo.h"
using namespace std;

class Test
{
public:
	int p1 = 1;
	bool p2 = false;
	std::string p3 = "p33333333";

	void testWithStack(StackInfo& stack)
	{
		int v1 = 0;
		std::string v2;
		Test v3;
		Test* v4 = nullptr;

		stack.pop<Test*>(v4);
		stack.pop(v3);
		stack.pop(v2);
		stack.pop(v1);
	
		std::cout << "testWithStack "
			<< v1 << " "
			<< v2 << " "
			<< v3.p3 << " "
			<< v4->p3 << std::endl;

		stack.push(1);
	}
};

void test2()
{
	Test t1;

	StackInfo stack;  // 实现此类，就俩模板函数，push和pop
	stack.push(111);
	stack.push<std::string>("asdfasdfasdf");

	Test t2;
	t2.p3 = "t2teststring";
	stack.push(t2);
	stack.push(&t1);

	t1.testWithStack(stack);

	int ret = 0;
	stack.pop(ret);
	std::cout << "testWithStack ret " << ret << std::endl;
}

int main() {
	test2();

	return 0;
}