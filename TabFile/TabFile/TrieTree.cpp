#include "TrieTree.h"

TrieTree::TrieTree()
{
	TrieTreeRoot = new TrieTreeNode();
}

TrieTree::~TrieTree()
{
	TrieTreeRoot->DeleteChildNodes();
	delete TrieTreeRoot;
}

TrieTreeNode* TrieTree::InsertString(const std::string& Str)
{
	TrieTreeNode* OPNode = TrieTreeRoot;
	for (int i = 0; i < Str.length(); ++i) {
		OPNode = OPNode->AddNewNode(Str[i]);
	}
	OPNode->bIsLeafNode = true;
	return OPNode;
}

void TrieTree::MergeNode()
{
	if (TrieTreeRoot)
	{
		TrieTreeRoot->MergeChildNode();
	}
}
