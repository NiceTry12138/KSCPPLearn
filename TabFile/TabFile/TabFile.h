#pragma once

#include "TrieTree.h"

class TabFile
{
public:
	

public:
	TabFile();
	~TabFile();

	void Load(const std::string& FilePath);
	void PrintAll();
	std::vector<std::string> Find(const std::string& KeyStr);

protected:
	std::string GetStrByNode(TrieTreeNode* Node);

private:
	std::vector<std::vector<TrieTreeNode*>> CellNodes;
	TrieTree* Root{ nullptr };
};

