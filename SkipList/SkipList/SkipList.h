#pragma once
#include "ListNode.h"
#include <vector>

using namespace std;

class SkipList
{
public:
	bool findDataByKey(int key, int &data);
	void deleteByKey(int key);
	void setNodeDataByKey(int key, int newData);
	bool insertNode(int key, int data);

	void PrintOneByOne();

	SkipList();
	~SkipList();
	static void deleteAllListNode(ListNode* root);

protected:
	static ListNode* findNodeByKey(const ListNode* frontNode, int key);
	static ListNode* findLessNodeByKey(ListNode* frontNode, int key, std::vector<ListNode*> &pathNode);

	int randomLevel(float p = 0.5f);

private:
	int m_Size{ 0 };
	ListNode* m_Head{ nullptr };
};