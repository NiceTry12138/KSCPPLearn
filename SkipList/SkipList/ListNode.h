#pragma once
#include <vector>

using namespace std;

struct ListNode
{
	int key{ 0 };
	int data{ 0 };
	std::vector<ListNode*> NextNodes{};
	std::vector<ListNode*> PreNodes{};

	ListNode(int _key, int _val, int _level) {
		key = _key;
		data = _val;
		for (int i = 0; i < _level; i++)
		{
			NextNodes.push_back(nullptr);
		}
		for (int i = 0; i < _level; i++)
		{
			PreNodes.push_back(nullptr);
		}
	}

	~ListNode() {
	}

	bool isEqual(const ListNode& other) {
		return other.data == this->data;
	}

	void setNextNode(ListNode* oldNode, ListNode* newNode) {
		setNode(NextNodes, oldNode, newNode);
	}

	void setPreNode(ListNode* oldNode, ListNode* newNode) {
		setNode(PreNodes, oldNode, newNode);
	}

protected:
	void setNode(std::vector<ListNode*>& list, ListNode* oldNode, ListNode* newNode) {
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i] == oldNode) {
				list[i] = newNode;
			}
		}
	}
};

