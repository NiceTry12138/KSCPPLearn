#pragma once
#include "ListNode.h"

class SkipList
{
public:
	int findDataByKey(int key);
	void deleteByKey(int key);
	void insertNode(int key, int data);

protected:
	static ListNode* findNodeByKey(const ListNode* frontNode, int key);

private:
	ListNode* m_Head{ nullptr };
};