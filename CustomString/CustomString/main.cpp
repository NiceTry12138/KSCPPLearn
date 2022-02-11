#include <iostream>
#include "CustomString.h"
#include <string>
using namespace std;

int main() {
	CustomString data = CustomString("Hello World");
	CustomString data1 = data;
	data1.append("123");
	CustomString data2 = CustomString(data);
	data2.append(data1);
	CustomString data3 = data2.sub(2, 10);
	std::cout << data << std::endl;
	std::cout << data1 << std::endl;
	std::cout << data2 << std::endl;
	std::cout << data3 << std::endl;
	system("pause");
	return 0;
}