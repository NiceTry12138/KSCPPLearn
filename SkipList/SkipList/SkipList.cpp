#include "SkipList.h"

int SkipList::findDataByKey(int key)
{
	auto result = findNodeByKey(m_Head, key);
	if (result != nullptr)
	{
		return result->data;
	}
	return 0;
}

ListNode* SkipList::findNodeByKey(const ListNode* frontNode, int key)
{
    int size = frontNode->NextNodes.size();
	for (int i = size-1; i >= 0; --i)
	{
		if (frontNode->NextNodes[i] == nullptr || frontNode->NextNodes[i]->key > key) {
			continue;
		}

		if (frontNode->NextNodes[i]->key == key)
		{
			return frontNode->NextNodes[i];
		}

		return findNodeByKey(frontNode->NextNodes[i], key);
	}
    return nullptr;
}
