#pragma once

template<typename T>
class CustomListNode
{
public:
	CustomListNode() : next(nullptr), behind(nullptr) {}
	CustomListNode(T data) : _data(data), next(nullptr), behind(nullptr) {}

	T _data;
	CustomListNode* next;
	CustomListNode* behind;
};