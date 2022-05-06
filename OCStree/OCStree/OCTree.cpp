#include "OCTree.h"

OCTree::OCTree(int _MaxDepth, int _XLength, int _YLength, int _ZLength)
{
	m_Depth = _MaxDepth;
	m_RootNode = new OCTreeNode(_XLength, 0, _YLength, 0, _XLength, 0);
	for (auto item : OCTreeNode::Directions())
	{
		CreateOCTreeNode(m_RootNode, item, _MaxDepth);
	}
}

OCTree::~OCTree()
{
	if (m_RootNode) {
		DeleteOCTreeNode(m_RootNode);
	}
}

inline int OCTree::GetMaxDepth()
{
	return m_Depth;
}

OCTreeNode* OCTree::GetOCTreeNode(int _posX, int _posY, int _posZ)
{
	return FindOCTreeNdoe(m_RootNode, _posX, _posY, _posZ);
}

inline void OCTree::CreateOCTreeNode(OCTreeNode* _Parent, OCTreeNodeDirection _Direction, int Depth)
{
	if (!_Parent || Depth == 0)
	{
		return;
	}
	auto BoxRange = OCTreeNode::GetBox(_Direction, _Parent);
	auto ChildNode = new OCTreeNode(BoxRange);
	_Parent->SetOCTreeNodeDirection(ChildNode, _Direction);
	for (auto item : OCTreeNode::Directions())
	{
		CreateOCTreeNode(ChildNode, item, Depth - 1);
	}
}

inline void OCTree::DeleteOCTreeNode(OCTreeNode* _Parent)
{
	if (_Parent == nullptr) {
		return;
	}

	for (auto it = _Parent->_Nodes.begin(); it != _Parent->_Nodes.end(); ++it)
	{
		DeleteOCTreeNode(it->second);
	}

	delete _Parent;
	_Parent = nullptr;
}

inline OCTreeNode* OCTree::FindOCTreeNdoe(OCTreeNode* _Parent, int _posX, int _posY, int _posZ)
{
	for (auto it = _Parent->_Nodes.begin(); it != _Parent->_Nodes.end(); ++it)
	{
		if (it->second && it->second->IsPointInBox(_posX, _posY, _posZ))
		{
			if (it->second->HasChild())
			{
				return FindOCTreeNdoe(it->second, _posX, _posY, _posZ);
			}
			else {
				return it->second;
			}
		}
	}
	return nullptr;
}
