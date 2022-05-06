#pragma once
#include "OCTreeLazeNode.h"

class OCTreeLaze
{
public:
	inline bool isPointInBox(Vec3 Point);

protected:


private:
	Vec3 m_Position;				// ����
	Vec3 m_BoxSize;					// �ߴ�
	OCTreeLazeNode m_Node;			// ��Ϣ�ڵ�
	OCTreeLaze* m_ChildNodes[8];	// �ӽڵ�
};

