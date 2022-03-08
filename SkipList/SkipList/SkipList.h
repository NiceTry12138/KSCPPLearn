#pragma once
#include "ListNode.h"
#include <vector>

using namespace std;

class SkipList
{
public:
	int findDataByKey(int key);
	void deleteByKey(int key);
	void insertNode(int key, int data);

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