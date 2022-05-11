#include <iostream>
#include "PosManager.h"
using namespace std;

int main() {
	auto m = new PosManager();
	int blockSize = 100;
	int mapSize = 10000;
	m->init(blockSize, mapSize);

	int poseId1 = 1;
	int poseId2 = 2;
	m->add(poseId1, 100, 200);  // 100是横坐标，200纵坐标
	m->add(poseId2, 200, 300);
	auto poseIds = m->find(poseId1);    // 找到poseid1脚下以及周围8格的所有id
	m->update(poseId1, 300, 400);
	m->remove(poseId2);

	for (auto item : poseIds)
	{
		std::cout << item << std::endl;
	}

	poseIds = m->find(poseId1);    // 找到poseid1脚下以及周围8格的所有id
	for (auto item : poseIds)
	{
		std::cout << item << std::endl;
	}

	delete m;
	return 0;
}