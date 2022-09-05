#include <iostream>
#include "ToolLibrary.h"
#include "TabFile.h"

struct InfoNode {
	std::string Name;
	double Height;
};

int main() {
	TabFile TabF;
	TabF.Load("test.txt");
	//TabF.PrintAll();
	auto Strs = TabF.Find("Haydn1");

	InfoNode Info;
	Info.Name = Strs[0];
	Info.Height = lexical_cast<double>(Strs[5]);
	std::cout << Info.Name << " " << Info.Height << std::endl;

	//TrieTree Tree;
	//Tree.InsertString("abcde");
	//Tree.InsertString("abcef");
	//Tree.InsertString("abc");
	//Tree.MergeNode();
	//std::cout << Tree.TrieTreeRoot->StrContent;

	return 0;
}

