#include "SensitiveWordHelper.h"
#include <iostream>
#include <fstream>
#include <string.h>

SensitiveWordHelper::SensitiveWordHelper()
{
	root = new Node();
}

SensitiveWordHelper::~SensitiveWordHelper()
{

}

void SensitiveWordHelper::load(const char* filename)
{
	std::ifstream ifs;
	ifs.open(filename, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "file open failed" << std::endl;
		return;
	}

	std::string buf;
	while (getline(ifs, buf))
	{
		addWords(root, buf.c_str());
	}

	ifs.close();
}

bool SensitiveWordHelper::check(const char* words)
{
	bool result = true;
	int len = strlen(words);
	Node* currentNode = root;
	for (int i = 0; i < len; ++i)
	{
		if (hasWord(currentNode, words[i]))
		{
			currentNode = currentNode->next[words[i] - 'a'];
		}
		else {
			result = false;
			break;
		}
	}
	return result;
}

void SensitiveWordHelper::printSelf()
{
	std::string out;
	deepPrint(root, out);
}

void SensitiveWordHelper::deepPrint(Node* node, std::string &str)
{
	bool hasChild = false;
	for (int i = 0; i < 26; ++i)
	{
		if (hasWord(node, 'a' + i))
		{
			str.push_back('a' + i);
			deepPrint(node->next[i], str);
			str.pop_back();
			hasChild = true;
		}
	}
	if (hasChild == false)
	{
		std::cout << str << std::endl;
	}
}

Node* SensitiveWordHelper::addWord(Node* node, char word)
{
	if (word >= 'A' && word <= 'Z')
	{
		word += 32;// 大写转小写
	}
	if (word < 'a' || word > 'z')	// 非字母 不做处理
	{
		return node;
	}
	if (hasWord(node, word))
	{
		return node->next[word - 'a'];
	}
	auto childNode = new Node(word);
	node->next[word - 'a'] = childNode;
	return childNode;
}

bool SensitiveWordHelper::hasWord(Node* node, char word)
{
	if (node->next[word - 'a'] != nullptr)
	{
		return true;
	}
	return false;
}

bool SensitiveWordHelper::addWords(Node* node, const char* words)
{
	auto rootNode = node;
	int len = strlen(words);
	for (int i = 0; i < len; ++i)
	{
		if ((words[i] >= 'A' && words[i] <= 'Z') || (words[i] >= 'a' && words[i] <= 'z'))
		{
			rootNode = addWord(rootNode, words[i]);
		}
	}
	return false;
}
