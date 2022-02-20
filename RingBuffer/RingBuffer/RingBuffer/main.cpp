#include <iostream>
#include "RingBuffer.h"
using namespace std;

int main() {
	int initSize = 32;
	const char* data = "123456789";
	auto buffer = RingBuffer(initSize);
	for (int ii = 0; ii < 1005; ii++)
	{
		buffer.push(data);  // 要支持自动扩容
	}
	for (int ii = 0; ii < 1005; ii++)
	{
		char out[128];
		buffer.pop(&out[0]);  // 要支持自动缩容
		std::cout << out << std::endl;
	}

	return 0;
}
