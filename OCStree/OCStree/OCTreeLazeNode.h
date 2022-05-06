#pragma once
struct Vec3 {
	int PosX;
	int PosY;
	int PosZ;

	Vec3(int x = 0, int y = 0, int z = 0) {
		PosX = x;
		PosY = y;
		PosZ = z;
	}

	inline bool operator ==(const Vec3& _Other) {
		return PosX == _Other.PosX && PosY == _Other.PosY && PosZ == _Other.PosZ;
	}
};

class OCTreeLazeNode
{
public:
	const Vec3& GetPosition();
	inline bool equal(const OCTreeLazeNode& other);
	OCTreeLazeNode(Vec3 Position);
protected:
	

private:
	Vec3 m_Position;
};

