#pragma once
#include <vector>
#include "Node.h"
class PosManager
{
public:
	void add(int _id, int _posX, int _posY);
	std::vector<int> find(int _id);
	void update(int _id, int _posX, int _posY);
	void remove(int _id);
	void init(int _blockSize, int _mapSize);

protected:
	void _add(int _id, int _posX, int _posY);
	void _leaveBlock(int _id);

private:
	int m_blockSize{ 0 };
	int m_mapSize{ 0 };

	Node* m_head{ nullptr };
	Node* m_tail{ nullptr };
};

