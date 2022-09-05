#include "TabFile.h"
#include <fstream>

void Stringsplit(const std::string& str, const std::string& splits, std::vector<std::string>& res)
{
	if (str == "")        return;
	//���ַ���ĩβҲ����ָ����������ȡ���һ��
	std::string strs = str + splits;
	size_t pos = strs.find(splits);
	int step = splits.size();

	// ���Ҳ����������ַ��������������� npos
	while (pos != strs.npos)
	{
		std::string temp = strs.substr(0, pos);
		res.push_back(temp);
		//ȥ���ѷָ���ַ���,��ʣ�µ��ַ����н��зָ�
		strs = strs.substr(pos + step, strs.size());
		pos = strs.find(splits);
	}
}


TabFile::TabFile()
{
	Root = new TrieTree();
}

TabFile::~TabFile()
{
	delete Root;
}

void TabFile::Load(const std::string& FilePath)
{
	std::ifstream Ifs;
	Ifs.open(FilePath);

	if (!Ifs.is_open())
	{
		std::cout << "Read Faild" << std::endl;
		return;
	}
	std::string Line;
	CellNodes.clear();
	while (getline(Ifs, Line))
	{
		std::vector<TrieTreeNode*> LineNodes;
		std::vector<std::string> Res;
		Stringsplit(Line, ",", Res);
		for (auto Str : Res)
		{
			TrieTreeNode* Node{ nullptr };
			if (Str.size() != 0)
			{
				Node = Root->InsertString(Str);
			}
			LineNodes.push_back(Node);
		}
		CellNodes.push_back(LineNodes);
	}
}

void TabFile::PrintAll()
{
	for (int i = 0; i < CellNodes.size(); ++i)
	{
		for (int j = 0; j < CellNodes[i].size(); ++j)
		{
			std::cout << GetStrByNode(CellNodes[i][j]) << " ";
		}
		std::cout << std::endl;
	}
}

std::vector<std::string> TabFile::Find(const std::string& KeyStr)
{
	std::vector<std::string> Result;
	std::vector<TrieTreeNode*> Nodes;
	for (int i = 0; i < CellNodes.size(); ++i)
	{
		if (CellNodes[i].size() <= 0)
		{
			continue;
		}
		auto LineKey = GetStrByNode(CellNodes[i][0]);
		if (LineKey != KeyStr)
		{
			continue;
		}
		Nodes = CellNodes[i];
		break;
	}
	for (int i = 0; i < Nodes.size(); ++i)
	{
		Result.push_back(GetStrByNode(Nodes[i]));
	}
	return Result;
}

std::string TabFile::GetStrByNode(TrieTreeNode * Node)
{
	if (Node == nullptr)
	{
		return "";
	}

	std::string Result;
	while (Node)
	{
		Result.insert(0, Node->StrContent);
		Node = Node->ParentNode;
	}
	return Result;
}
