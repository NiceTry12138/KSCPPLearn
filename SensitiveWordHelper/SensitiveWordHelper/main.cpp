#include <iostream>
#include "SensitiveWordHelper.h"
using namespace std;

int main() {

	auto m = new SensitiveWordHelper();
	m->load("xxxxFile.txt");
	//m->printSelf();

	bool ret = m->check("xxx");

	if (ret)
	{
		std::cout << "true" << std::endl;
	}
	else {
		std::cout << "false" << std::endl;
	}

	return 0;
}