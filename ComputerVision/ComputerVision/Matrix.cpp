#define _USE_MATH_DEFINES
#include <cmath>
#include "Matrix.h"



Matrix::Matrix()
{
	
}


Matrix::~Matrix()
{
}

Matrix Matrix::identity()
{
	Matrix m;
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			m.data[r][c] = 0;			
		}
	}

	m.data[0][0] = 1;
	m.data[1][1] = 1;
	m.data[2][2] = 1;
	m.data[3][3] = 1;
	return m;
}

Matrix Matrix::rotation(Vec3f & axis, float angle)
{
	Matrix rotation = identity();
	float c, s;
	angle = angle / 180 * M_PI;
	c = cos(angle);
	s = sin(angle);

	rotation.data[0][0] = (float)(pow(axis.x, 2)*(1 - c) + c);
	rotation.data[0][1] = (axis.x*axis.y*(1 - c) - axis.z*s);
	rotation.data[0][2] = (axis.x*axis.z*(1 - c) + axis.y*s);

	rotation.data[1][0] = (axis.x*axis.y*(1 - c) + axis.z*s);
	rotation.data[1][1] = (float)(pow(axis.y, 2)*(1 - c) + c);
	rotation.data[1][2] = (axis.y*axis.z*(1 - c) - axis.x*s);

	rotation.data[2][0] = (axis.x*axis.z*(1 - c) - axis.y*s);
	rotation.data[2][1] = (axis.y*axis.z*(1 - c) + axis.x*s);
	rotation.data[2][2] = (float)(pow(axis.z, 2)*(1 - c) + c);

	return rotation;
}

Matrix Matrix::translate(Vec3f &offset)
{
	Matrix translation = identity();

	translation.data[0][3] = offset.x;
	translation.data[1][3] = offset.y;
	translation.data[2][3] = offset.z;

	return translation;
}

Vec3f Matrix::operator*(const Vec3f & vec)
{
	float x, y, z;
		x = (data[0][0] * vec.x) + (data[0][1] * vec.y) + (data[0][2] * vec.z) + data[0][3];
		y = (data[1][0] * vec.x) + (data[1][1] * vec.y) + (data[1][2] * vec.z) + data[1][3];
		z = (data[2][0] * vec.x) + (data[2][1] * vec.y) + (data[2][2] * vec.z) + data[2][3];
	
		return Vec3f(x, y, z);
}

Matrix Matrix::operator*(const Matrix &other)
{
	Matrix result = Matrix::identity();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.data[i][j] = 0;
			for (int k = 0; k < 4; k++)
				result.data[i][j] = result.data[i][j] + data[i][k] * other.data[k][j];
		}
	}
	
	return result;
}

//Vec3f Matrix::operator*(Matrix &mat, Vec3f & vec)
//{
//	float x, y, z;
//	x = (mat.data[0][0] * vec.x) + (mat.data[0][1] * vec.y) + (mat.data[0][2] * vec.z) + mat.data[0][3];
//	y = (mat.data[1][0] * vec.x) + (mat.data[1][1] * vec.y) + (mat.data[1][2] * vec.z) + mat.data[1][3];
//	z = (mat.data[2][0] * vec.x) + (mat.data[2][1] * vec.y) + (mat.data[2][2] * vec.z) + mat.data[2][3];
//
//	return Vec3f(x, y, z);
//}
//
//Matrix Matrix::operator*(Matrix &mat1, Matrix &mat2)
//{
//	Matrix result = Matrix::identity();
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			result.data[i][j] = 0;
//			for (int k = 0; k < 4; k++)
//				result.data[i][j] = result.data[i][j] + mat1.data[i][k] * mat2.data[k][j];
//		}
//	}
//
//	return result;
//}




