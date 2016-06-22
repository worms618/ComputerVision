#pragma once
#include "Vector.h"

class Matrix
{
public:	
	~Matrix();

	static Matrix identity();
	static Matrix rotation(Vec3f &, float angle);
	static Matrix translate(Vec3f &);

	Vec3f operator*(const Vec3f &);
	Matrix operator*(const Matrix&);
	float data[4][4];
private:
	Matrix();
	
};

