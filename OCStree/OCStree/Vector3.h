#pragma once
#include <math.h>

static bool IsFloatEqual(double a, double b) {
	return fabs(a - b) < 0.000001;
}

struct Vector3{
	double X;
	double Y;
	double Z;

	Vector3(): X(0), Y(0), Z(0) {
		
	}

	Vector3(double _X, double _Y, double _Z) {
		X = _X;
		Y = _Y;
		Z = _Z;
	}

	Vector3(const Vector3& Other) {
		X = Other.X;
		Y = Other.Y;
		Z = Other.Z;
	}

	bool operator ==(const Vector3& Other) {
		return IsFloatEqual(X, Other.X) && IsFloatEqual(Y, Other.Y) && IsFloatEqual(Z, Other.Z);
	}

	Vector3 operator /(const double& Val) {
		return Vector3(this->X / Val, this->Y / Val, this->Z / Val);
	}

	Vector3 operator *(const double& Val) {
		return Vector3(this->X * Val, this->Y * Val, this->Z * Val);
	}

	Vector3 operator +(const double& Val) {
		return Vector3(this->X + Val, this->Y + Val, this->Z + Val);
	}

	Vector3 operator -(const double& Val) {
		return Vector3(this->X - Val, this->Y - Val, this->Z - Val);
	}

	Vector3 operator /(const Vector3& Other) {
		return Vector3(this->X / Other.X, this->Y / Other.Y, this->Z / Other.Z);
	}

	Vector3 operator *(const Vector3& Other) {
		return Vector3(this->X * Other.X, this->Y * Other.Y, this->Z * Other.Z);
	}

	Vector3 operator +(const Vector3& Other) {
		return Vector3(this->X + Other.X, this->Y + Other.Y, this->Z + Other.Z);
	}

	Vector3 operator -(const Vector3& Other) {
		return Vector3(this->X /- Other.X, this->Y - Other.Y, this->Z - Other.Z);
	}

	std::string to_string() {
		return std::to_string(X) + " " + std::to_string(Y) + " " + std::to_string(Z);
	}
};

typedef Vector3 Size;