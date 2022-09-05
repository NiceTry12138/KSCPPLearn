#pragma once
#include <utility>
#include <vector>
#include <string>
#include <iostream>

struct TrieTreeNode;

typedef std::pair<char, TrieTreeNode*> TrieTreeNodePair;

struct TrieTreeNode {
	std::vector<TrieTreeNodePair> NextNodes;
	TrieTreeNode* ParentNode{ nullptr };
	char SelfKey;
	std::string StrContent;
	bool bIsLeafNode{ false };	// р╤вс╫з╣Ц

	TrieTreeNode(char Key, TrieTreeNode* Parent) {
		ParentNode = Parent;
		SelfKey = Key;
		StrContent.push_back(Key);
	}

	TrieTreeNode() {
	}

	~TrieTreeNode() {
	}

	TrieTreeNode* GetNextNode(char Key) {
		for (auto Item : NextNodes)
		{
			if (Item.first == Key)
			{
				return Item.second;
			}
		}
		return nullptr;
	}

	TrieTreeNode* AddNewNode(char Key) {
		TrieTreeNode* NextNode = GetNextNode(Key);
		if (NextNode != nullptr)
		{
			return NextNode;
		}

		NextNode = new TrieTreeNode(Key, this);
		NextNodes.push_back(std::make_pair(Key, NextNode));
		return NextNode;
	}

	void MergeChildNode() {
		int NextNodeSize = NextNodes.size();
		if (NextNodeSize == 0)
		{
			return;
		}

		for (auto Item : NextNodes)
		{
			Item.second->MergeChildNode();
		}

		if (NextNodeSize > 1)
		{
			return;
		}
		if (NextNodes[0].second->bIsLeafNode)
		{
			return;
		}

		//std::cout << SelfKey << " Merge Start " << std::endl;
			 
		auto Node = NextNodes[0];
		NextNodes.clear();

		//std::cout << Node.second->StrContent << " NextNode StrContent" << std::endl;

		StrContent += Node.second->StrContent;
		NextNodes = Node.second->NextNodes;
		for (auto Node : NextNodes)
		{
			Node.second->ParentNode = this;
		}

		//std::cout << StrContent << " CurrentNode StrContent" << std::endl;

		delete Node.second;
	}

	void DeleteChildNodes() {
		for (auto Item : NextNodes)
		{
			delete Item.second;
		}
	}
};

class TrieTree
{
public:
	TrieTree();
	~TrieTree();

	TrieTreeNode* InsertString(const std::string& Str);
	void MergeNode();

//private:
	TrieTreeNode* TrieTreeRoot{ nullptr };
};

