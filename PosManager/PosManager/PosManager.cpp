#include "PosManager.h"
#include <math.h>

void PosManager::add(int _id, int _posX, int _posY)
{
	_add(_id, _posX, _posY);
}

std::vector<int> PosManager::find(int _id)
{
	int _posX = 0, _posY = 0;
	auto node = _findByID(_id);
	auto result = std::vector<int>();
	if (!node)
	{
		return result;
	}
	_posX = node->m_posX;
	_posY = node->m_posY;
	int minPosX = _posX - m_blockSize;
	int maxPosX = _posX + m_blockSize;
	int minPosY = _posY - m_blockSize;
	int maxPosY = _posY + m_blockSize;

	auto currentNode = m_head->xNext;
	while (currentNode != m_tail)
	{
		if (currentNode->m_posX > maxPosX)
		{
			break;
		}
		if (currentNode->m_posX >= minPosX && currentNode->m_posY >= minPosY && currentNode->m_posY <= maxPosY)
		{
			result.push_back(currentNode->m_id);
		}
		currentNode = currentNode->xNext;
	}
	return result;
}

void PosManager::update(int _id, int _posX, int _posY)
{
	auto node = _leaveBlock(_id);
	if (node)
	{
		node->m_posX = _posX;
		node->m_posY = _posY;
		_add(node);
	}
	else {
		_add(_id, _posX, _posY);
	}
}

void PosManager::remove(int _id)
{
	auto node = _leaveBlock(_id);
	delete node;
}

void PosManager::init(int _blockSize, int _mapSize)
{
	m_blockSize = _blockSize;
	m_mapSize = _mapSize;
}

PosManager::PosManager()
{
	m_head = new Node(-1, INT_MIN, INT_MIN);
	m_tail = new Node(-1, INT_MAX, INT_MAX);

	m_head->xNext = m_tail;
	m_head->yNext = m_tail;
	m_tail->xPrev = m_head;
	m_tail->yPrev = m_head;
}

PosManager::~PosManager()
{
}

Node* PosManager::_add(int _id, int _posX, int _posY)
{
	Node* temp = new Node(_id, _posX, _posY);
	return _add(temp);
}

Node* PosManager::_add(Node* _node)
{
	Node* currentNode = m_head->xNext;
	while (currentNode != nullptr)
	{
		if (currentNode->m_posX > _node->m_posX || currentNode == m_tail)
		{
			insertBefore(_node, currentNode, Axis::AXIS_X);
		}
		currentNode = currentNode->xNext;
	}
	currentNode = m_head->yNext;
	while (currentNode)
	{
		if (currentNode->m_posY > _node->m_posY || currentNode == m_tail)
		{
			insertBefore(_node, currentNode, Axis::AXIS_Y);
		}
		currentNode = currentNode->yNext;
	}
	return _node;
}

Node* PosManager::_leaveBlock(int _id)
{
	auto currentNode = _findByID(_id);
	if (currentNode)
	{
		removeNode(currentNode);
	}
	else {
		return nullptr;
	}
	return currentNode;
}

Node* PosManager::_findByID(int _id)
{
	auto currentNode = m_head->xNext;
	while (currentNode != m_tail)
	{
		if (currentNode->m_id == _id)
		{
			break;
		}
		currentNode = currentNode->xNext;
	}
	if (m_tail == currentNode)
	{
		return nullptr;
	}
	return currentNode;
}

void PosManager::insertBefore(Node* _before, Node* _next, Axis _asix)
{
	switch (_asix)
	{
	case PosManager::Axis::AXIS_X:
		_before->xNext = _next;
		_before->xPrev = _next->xPrev;
		_next->xPrev->xNext = _before;
		_next->xPrev = _before;
		break;
	case PosManager::Axis::AXIS_Y:
		_before->yNext = _next;
		_before->yPrev = _next->yPrev;
		_next->yPrev->yNext = _before;
		_next->yPrev = _before;
		break;
	}
}

void PosManager::removeNode(Node* _node)
{
	_node->xNext->xPrev = _node->xPrev;
	_node->xPrev->xNext = _node->xNext;
	_node->yNext->yPrev = _node->yPrev;
	_node->yPrev->yNext = _node->yNext;

	_node->xNext = nullptr;
	_node->yNext = nullptr;
	_node->yPrev = nullptr;
	_node->xPrev = nullptr;
}

int PosManager::getLessVal(int val, int modval)
{
	int result = 0;
	int rate = abs(val / modval);
	if (val < 0)
	{
		return -modval * (rate + 1);
	}
	else {
		return modval * rate;
	}
}
