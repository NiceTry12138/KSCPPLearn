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

	PosManager();
	~PosManager();

protected:
	enum class Axis
	{
		AXIS_X,
		AXIS_Y
	};

	Node* _add(int _id, int _posX, int _posY);
	Node* _add(Node* _node);
	Node* _leaveBlock(int _id);
	Node* _findByID(int _id);

	static void insertBefore(Node* _before, Node* _next, Axis _asix);
	static void removeNode(Node* _node);
	static int getLessVal(int val, int modval);
private:
	int m_blockSize{ 0 };
	int m_mapSize{ 0 };

	Node* m_head{ nullptr };
	Node* m_tail{ nullptr };
};

