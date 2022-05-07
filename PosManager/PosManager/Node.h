#pragma once
class Node
{
public:
	Node(int _id, int _posX, int _posY) :m_id(_id), m_posX(_posX), m_posY(_posY) {

	}
	~Node() {

	}

	Node* xPrev{ nullptr };
	Node* xNext{ nullptr };
	Node* yPrev{ nullptr };
	Node* yNext{ nullptr };

	int m_id;
	int m_posX;
	int m_posY;
};