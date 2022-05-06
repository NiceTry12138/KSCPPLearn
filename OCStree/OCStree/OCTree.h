#pragma once
#include "OCTreeNode.h"

class OCTree
{
public:
	OCTree(int _MaxDepth, int _XLength, int _YLength, int _ZLength);
	~OCTree();
	int GetMaxDepth();
	OCTreeNode* GetOCTreeNode(int _posX, int _posY, int _posZ);

protected:
	void CreateOCTreeNode(OCTreeNode* _Parent, OCTreeNodeDirection _Direction, int Depth);
	void DeleteOCTreeNode(OCTreeNode* _Parent);
	OCTreeNode* FindOCTreeNdoe(OCTreeNode* _Parent, int _posX, int _posY, int _posZ);
private:
	OCTreeNode* m_RootNode{ nullptr };
	int m_Depth{ 0 };
};