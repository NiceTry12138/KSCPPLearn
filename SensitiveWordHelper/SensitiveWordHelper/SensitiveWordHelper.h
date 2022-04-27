#pragma once
#include <string>
struct Node {
	char word = 0;
	Node* next[26] = {};

	Node() {
		word = 0;
		for (int i = 0; i < 26; i++)
		{
			next[i] = nullptr;
		}
	}

	Node(char w) {
		word = w;
		for (int i = 0; i < 26; i++)
		{
			next[i] = nullptr;
		}
	}
};

class SensitiveWordHelper
{
public:
	SensitiveWordHelper();
	~SensitiveWordHelper();

	void load(const char* filename);
	bool check(const char* words);

	void printSelf();
protected:
	static Node* addWord(Node* node, char word);
	static bool hasWord(Node* node, char word);
	static bool addWords(Node* node, const char* words);

	void deepPrint(Node* node, std::string &str);
private:
	Node* root = nullptr;
};

