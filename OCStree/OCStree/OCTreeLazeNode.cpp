#include "OCTreeLazeNode.h"

const Vec3& OCTreeLazeNode::GetPosition()
{
    // TODO: �ڴ˴����� return ���
    return m_Position;
}

inline bool OCTreeLazeNode::equal(const OCTreeLazeNode& other)
{
    return m_Position == other.m_Position;
}

OCTreeLazeNode::OCTreeLazeNode(Vec3 Position)
{
    m_Position = Position;
}
