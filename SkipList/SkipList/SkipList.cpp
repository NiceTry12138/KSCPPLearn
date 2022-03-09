#include "SkipList.h"
#include <iostream>
#include <cmath>

#define RANDOM01 (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))

bool SkipList::findDataByKey(int key, int &data)
{
	std::cout << "find target node " << key << " => ";
	auto result = findNodeByKey(m_Head, key);
	if (result != nullptr)
	{
		data = result->data;
		return true;
	}
	std::cout << "not find " << key << std::endl;
	return false;
}

void SkipList::deleteByKey(int key)
{
	std::cout << "delete target node " << key << " => ";
	auto result = findNodeByKey(m_Head, key);
	if (result == nullptr) {
		return;
	}

	for (int i = 0; i < result->NextNodes.size(); i++)
	{
		if (result->NextNodes[i] == nullptr || result->PreNodes[i] == nullptr)
		{
			continue;
		}

		result->NextNodes[i]->setPreNode(result, result->PreNodes[i]);
		result->PreNodes[i]->setNextNode(result, result->NextNodes[i]);
	}
	delete result;
	--m_Size;
}

void SkipList::setNodeDataByKey(int key, int newData)
{
	auto result = findNodeByKey(m_Head, key);
	result->data = newData;
}

bool SkipList::insertNode(int key, int data)
{
	std::cout << "insert target node " << key << " => ";
	auto findNode = findNodeByKey(m_Head, key);
	if (findNode != nullptr)
	{
		return false;
	}

	std::vector<ListNode*> path;
	auto lessKeyNode = findLessNodeByKey(m_Head, key, path);
	int level = randomLevel();
	//std::cout << key << " " << level << std::endl;
	auto node = new ListNode(key, data, level);
	std::reverse(path.begin(), path.end());

	int currentLevel = 0;
	for (int i = 0; i < path.size() && currentLevel < level; i++)
	{
		if (path[i]->NextNodes.size() > currentLevel && (path[i]->NextNodes[currentLevel] == nullptr|| path[i]->NextNodes[currentLevel]->key > key))
		{
			node->NextNodes[currentLevel] = path[i]->NextNodes[currentLevel];
			if (path[i]->NextNodes[currentLevel] != nullptr)
			{
				path[i]->NextNodes[currentLevel]->PreNodes[currentLevel] = node;
			}

			path[i]->NextNodes[currentLevel] = node;
			node->PreNodes[currentLevel] = path[i];

			currentLevel++;
		}
	}

	++m_Size;

	return true;
}

void SkipList::PrintOneByOne()
{
	ListNode* node = m_Head;
	while (node != nullptr)
	{
		std::cout << node->data << " ";
		if (node->NextNodes.size() > 0)
		{
			node = node->NextNodes[0];
		}
		else {
			break;
		}
	}
	std::cout << std::endl; 
	
	node = m_Head;
	while (node != nullptr)
	{
		for (auto midnode : node->NextNodes) {
			if (midnode)
			{
				std::cout << node->key << " -> " << midnode->key << std::endl;
			}
		}
		std::cout << " --------- " << std::endl;
		if (node->NextNodes.size() > 0)
		{
			node = node->NextNodes[0];
		}
		else {
			break;
		}
	}
}

SkipList::SkipList()
{
	m_Head = new ListNode(-1, -1, 10);
}

SkipList::~SkipList()
{
	deleteAllListNode(m_Head);
}

ListNode* SkipList::findNodeByKey(const ListNode* frontNode, int key)
{
	int size = frontNode->NextNodes.size();
	std::cout << frontNode->key << " -> ";
	for (int i = size-1; i >= 0; --i)
	{
		if (frontNode->NextNodes[i] == nullptr || frontNode->NextNodes[i]->key > key) {
			continue;
		}

		if (frontNode->NextNodes[i]->key == key)
		{
			std::cout << frontNode->NextNodes[i]->key << std::endl;
			return frontNode->NextNodes[i];
		}

		return findNodeByKey(frontNode->NextNodes[i], key);
	}
    return nullptr;
}

ListNode* SkipList::findLessNodeByKey(ListNode* frontNode, int key, std::vector<ListNode*> &pathNode)
{
	int size = frontNode->NextNodes.size();
	pathNode.push_back(frontNode);
	for (int i = size - 1; i >= 0; -- i)
	{
		if (frontNode->NextNodes[i] == nullptr || frontNode->NextNodes[i]->data > key)
		{
			continue;
		}

		if (frontNode->NextNodes[i]->data < key) {
			return findLessNodeByKey(frontNode->NextNodes[i], key, pathNode);
		}
	}
	return frontNode;
}

void SkipList::deleteAllListNode(ListNode* root)
{
	if (root == nullptr) {
		return;
	}
	if (root->NextNodes.size() > 0)
	{
		deleteAllListNode(root->NextNodes[0]);
	}
	delete root;
}

int SkipList::randomLevel(float p)
{
	int level = 1; 
	int maxLevel = log(m_Size);
	while (RANDOM01 < p && level <= maxLevel)
	{
		++level;
	}
	return level;
}
