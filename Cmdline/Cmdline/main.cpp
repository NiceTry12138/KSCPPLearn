// Cmdline.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Defines.h"

void testPrint(int age, bool isPrintAge) {
	if (isPrintAge)
	{
		std::cout << "age = " << age << std::endl;
	}
}

// Cmdline.exe -a=12 -p
int main(int argc, char* argv[])
{
	Command cmd;
	cmd.add("Age", 'a', 10, true, "age");
	cmd.add("Print", 'p', false, "isPrint");

	cmd.parse(argc, argv);

	std::cout << cmd.get<int>("Age") << std::endl;
	std::cout << cmd.get<int>('a') << std::endl;

	std::cout << cmd.isSet("Age") << std::endl;
	std::cout << cmd.isSet('a') << std::endl;

	std::cout << cmd.isSet("Print") << std::endl;
	std::cout << cmd.isSet('p') << std::endl;

	testPrint(cmd.get<int>('a'), cmd.isSet('p'));
	return 0;
}