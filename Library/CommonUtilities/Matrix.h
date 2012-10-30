#ifndef _MATRIX_44_H_
#define _MATRIX_44_H_
#include "Vector.h"
#include <d3d10.h>
#include <d3dx10.h>

template <class Type> class Matrix33;

template <class Type>
class Matrix44
{
public:
	Matrix44();
	~Matrix44();

	void Init(float* aFloatArrayPointer);

	Matrix44<Type> operator+(const Matrix44<Type> &aMatrix) const;
	Matrix44<Type> operator-(const Matrix44<Type> &aMatrix) const;
	Matrix44<Type> operator*(const Matrix33<Type> &aMatrix) const;
	Matrix44<Type> operator*(const Matrix44<Type> &aMatrix) const;
	Matrix44<Type>& operator*=(const Matrix44<Type> &aMatrix);
	Matrix44<Type>& operator=(const Matrix44<Type> &aMatrix);
	//Matrix44<Type>& operator=(const Type* aMatrix);
	bool operator==(const Matrix44<Type> &aMatrix) const;

	Matrix33<Type> Get33() const;
	void Set33(const Matrix33<Type> &aMatrix33);
	void SetPosition(const Vector3<Type> &aPosition);
	Vector3<Type> GetPosition() const;
	Matrix44<Type> Inverse() const;
	Matrix44<Type> TransposeInverse() const;

	static Matrix44<Type> CreateRotateAroundX(Type aAngleInRadians);
	static Matrix44<Type> CreateRotateAroundY(Type aAngleInRadians);
	static Matrix44<Type> CreateRotateAroundZ(Type aAngleInRadians);
	static Matrix44<Type> Identity();

	void operator =(D3DXMATRIX aMatrix);
	void NormalizeIndividualVectors();
	Vector4<Type> GetXVector();
	Vector4<Type> GetYVector();
	Vector4<Type> GetZVector();

public:
	static const int ourSize = 16;
	Type myMatrix[ourSize];
};

template <class Type>
Matrix44<Type>::Matrix44()
{
	myMatrix[0] = 1;
	myMatrix[1] = 0;
	myMatrix[2] = 0;
	myMatrix[3] = 0;
	
	myMatrix[4] = 0;
	myMatrix[5] = 1;
	myMatrix[6] = 0;
	myMatrix[7] = 0;

	myMatrix[8] = 0;
	myMatrix[9] = 0;
	myMatrix[10] = 1;
	myMatrix[11] = 0;

	myMatrix[12] = 0;
	myMatrix[13] = 0;
	myMatrix[14] = 0;
	myMatrix[15] = 1;
}

template <class Type>
Matrix44<Type>::~Matrix44()
{

}

template <class Type>
void Matrix44<Type>::Init(float* aFloatArrayPointer)
{
	for (int index = 0; index < ourSize; index++)
	{
		myMatrix[index] = aFloatArrayPointer[index];
	}
}

template <class Type>
Matrix44<Type> Matrix44<Type>::Identity()
{
	Matrix44<Type> matrix;

	matrix.myMatrix[0] = 1;
	matrix.myMatrix[1] = 0;
	matrix.myMatrix[2] = 0;
	matrix.myMatrix[3] = 0;

	matrix.myMatrix[4] = 0;
	matrix.myMatrix[5] = 1;
	matrix.myMatrix[6] = 0;
	matrix.myMatrix[7] = 0;

	matrix.myMatrix[8] = 0;
	matrix.myMatrix[9] = 0;
	matrix.myMatrix[10] = 1;
	matrix.myMatrix[11] = 0;

	matrix.myMatrix[12] = 0;
	matrix.myMatrix[13] = 0;
	matrix.myMatrix[14] = 0;
	matrix.myMatrix[15] = 1;

	return matrix;
}

template <class Type>
bool Matrix44<Type>::operator==(const Matrix44<Type> &aMatrix) const
{
	for (int index = 0; index < ourSize; index++)
	{
		if (myMatrix[index] != aMatrix.myMatrix[index])
		{
			return false;
		}
	}
	return true;
}

template <class Type>
Matrix44<Type>& Matrix44<Type>::operator=(const Matrix44<Type> &aMatrix)
{
	for (int index = 0; index < ourSize; index++)
	{
		myMatrix[index] = aMatrix.myMatrix[index];
	}
	return (*this);
}

//template <class Type>
//Matrix44<Type>& Matrix44<Type>::operator=(const Type* aMatrix)
//{
//	for( int index = 0; index < ourSize; index++ )
//	{
//		myMatrix[index] = aMatrix[index];
//	}
//	return (*this);
//}

template <class Type>
Matrix44<Type>& Matrix44<Type>::operator*=(const Matrix44<Type> &aMatrix)
{
	Type matrix[ourSize];

	matrix[0]  = myMatrix[0]*aMatrix.myMatrix[0] + myMatrix[1]*aMatrix.myMatrix[4] + myMatrix[2]*aMatrix.myMatrix[8] + myMatrix[3]*aMatrix.myMatrix[12];
	matrix[1]  = myMatrix[0]*aMatrix.myMatrix[1] + myMatrix[1]*aMatrix.myMatrix[5] + myMatrix[2]*aMatrix.myMatrix[9] + myMatrix[3]*aMatrix.myMatrix[13];
	matrix[2]  = myMatrix[0]*aMatrix.myMatrix[2] + myMatrix[1]*aMatrix.myMatrix[6] + myMatrix[2]*aMatrix.myMatrix[10] + myMatrix[3]*aMatrix.myMatrix[14];
	matrix[3]  = myMatrix[0]*aMatrix.myMatrix[3] + myMatrix[1]*aMatrix.myMatrix[7] + myMatrix[2]*aMatrix.myMatrix[11] + myMatrix[3]*aMatrix.myMatrix[15];

	matrix[4]  = myMatrix[4]*aMatrix.myMatrix[0] + myMatrix[5]*aMatrix.myMatrix[4] + myMatrix[6]*aMatrix.myMatrix[8] + myMatrix[7]*aMatrix.myMatrix[12];
	matrix[5]  = myMatrix[4]*aMatrix.myMatrix[1] + myMatrix[5]*aMatrix.myMatrix[5] + myMatrix[6]*aMatrix.myMatrix[9] + myMatrix[7]*aMatrix.myMatrix[13];
	matrix[6]  = myMatrix[4]*aMatrix.myMatrix[2] + myMatrix[5]*aMatrix.myMatrix[6] + myMatrix[6]*aMatrix.myMatrix[10] + myMatrix[7]*aMatrix.myMatrix[14];
	matrix[7]  = myMatrix[4]*aMatrix.myMatrix[3] + myMatrix[5]*aMatrix.myMatrix[7] + myMatrix[6]*aMatrix.myMatrix[11] + myMatrix[7]*aMatrix.myMatrix[15];

	matrix[8]  = myMatrix[8]*aMatrix.myMatrix[0] + myMatrix[9]*aMatrix.myMatrix[4] + myMatrix[10]*aMatrix.myMatrix[8] + myMatrix[11]*aMatrix.myMatrix[12];
	matrix[9]  = myMatrix[8]*aMatrix.myMatrix[1] + myMatrix[9]*aMatrix.myMatrix[5] + myMatrix[10]*aMatrix.myMatrix[9] + myMatrix[11]*aMatrix.myMatrix[13];
	matrix[10] = myMatrix[8]*aMatrix.myMatrix[2] + myMatrix[9]*aMatrix.myMatrix[6] + myMatrix[10]*aMatrix.myMatrix[10] + myMatrix[11]*aMatrix.myMatrix[14];
	matrix[11] = myMatrix[8]*aMatrix.myMatrix[3] + myMatrix[9]*aMatrix.myMatrix[7] + myMatrix[10]*aMatrix.myMatrix[11] + myMatrix[11]*aMatrix.myMatrix[15];

	matrix[12] = myMatrix[12]*aMatrix.myMatrix[0] + myMatrix[13]*aMatrix.myMatrix[4] + myMatrix[14]*aMatrix.myMatrix[8] + myMatrix[15]*aMatrix.myMatrix[12];
	matrix[13] = myMatrix[12]*aMatrix.myMatrix[1] + myMatrix[13]*aMatrix.myMatrix[5] + myMatrix[14]*aMatrix.myMatrix[9] + myMatrix[15]*aMatrix.myMatrix[13];
	matrix[14] = myMatrix[12]*aMatrix.myMatrix[2] + myMatrix[13]*aMatrix.myMatrix[6] + myMatrix[14]*aMatrix.myMatrix[10] + myMatrix[15]*aMatrix.myMatrix[14];
	matrix[15] = myMatrix[12]*aMatrix.myMatrix[3] + myMatrix[13]*aMatrix.myMatrix[7] + myMatrix[14]*aMatrix.myMatrix[11] + myMatrix[15]*aMatrix.myMatrix[15];

	for (int index = 0; index < ourSize; index++)
	{
		myMatrix[index] = matrix[index];
	}

	return (*this);
}

template <class Type>
Matrix44<Type> Matrix44<Type>::operator*(const Matrix33<Type> &aMatrix) const
{
	Matrix44<Type> matrix;

	matrix.myMatrix[0]  = myMatrix[0]*aMatrix.myMatrix[0] + myMatrix[1]*aMatrix.myMatrix[3] + myMatrix[2]*aMatrix.myMatrix[6];
	matrix.myMatrix[1]  = myMatrix[0]*aMatrix.myMatrix[1] + myMatrix[1]*aMatrix.myMatrix[4] + myMatrix[2]*aMatrix.myMatrix[7];
	matrix.myMatrix[2]  = myMatrix[0]*aMatrix.myMatrix[2] + myMatrix[1]*aMatrix.myMatrix[5] + myMatrix[2]*aMatrix.myMatrix[8];
	matrix.myMatrix[3]  = myMatrix[3];

	matrix.myMatrix[4]  = myMatrix[4]*aMatrix.myMatrix[0] + myMatrix[5]*aMatrix.myMatrix[3] + myMatrix[6]*aMatrix.myMatrix[6];
	matrix.myMatrix[5]  = myMatrix[4]*aMatrix.myMatrix[1] + myMatrix[5]*aMatrix.myMatrix[4] + myMatrix[6]*aMatrix.myMatrix[7];
	matrix.myMatrix[6]  = myMatrix[4]*aMatrix.myMatrix[2] + myMatrix[5]*aMatrix.myMatrix[5] + myMatrix[6]*aMatrix.myMatrix[8];
	matrix.myMatrix[7]  = myMatrix[7];

	matrix.myMatrix[8]  = myMatrix[8]*aMatrix.myMatrix[0] + myMatrix[9]*aMatrix.myMatrix[3] + myMatrix[10]*aMatrix.myMatrix[6];
	matrix.myMatrix[9]  = myMatrix[8]*aMatrix.myMatrix[1] + myMatrix[9]*aMatrix.myMatrix[4] + myMatrix[10]*aMatrix.myMatrix[7];
	matrix.myMatrix[10] = myMatrix[8]*aMatrix.myMatrix[2] + myMatrix[9]*aMatrix.myMatrix[5] + myMatrix[10]*aMatrix.myMatrix[8];
	matrix.myMatrix[11] = myMatrix[11];

	matrix.myMatrix[12] = myMatrix[12];
	matrix.myMatrix[13] = myMatrix[13];
	matrix.myMatrix[14] = myMatrix[14];
	matrix.myMatrix[15] = myMatrix[15];

	return matrix;
}

template <class Type>
Matrix44<Type> Matrix44<Type>::operator*(const Matrix44<Type> &aMatrix) const
{
	Matrix44<Type> matrix;

	matrix.myMatrix[0]  = myMatrix[0]*aMatrix.myMatrix[0] + myMatrix[1]*aMatrix.myMatrix[4] + myMatrix[2]*aMatrix.myMatrix[8] + myMatrix[3]*aMatrix.myMatrix[12];
	matrix.myMatrix[1]  = myMatrix[0]*aMatrix.myMatrix[1] + myMatrix[1]*aMatrix.myMatrix[5] + myMatrix[2]*aMatrix.myMatrix[9] + myMatrix[3]*aMatrix.myMatrix[13];
	matrix.myMatrix[2]  = myMatrix[0]*aMatrix.myMatrix[2] + myMatrix[1]*aMatrix.myMatrix[6] + myMatrix[2]*aMatrix.myMatrix[10] + myMatrix[3]*aMatrix.myMatrix[14];
	matrix.myMatrix[3]  = myMatrix[0]*aMatrix.myMatrix[3] + myMatrix[1]*aMatrix.myMatrix[7] + myMatrix[2]*aMatrix.myMatrix[11] + myMatrix[3]*aMatrix.myMatrix[15];

	matrix.myMatrix[4]  = myMatrix[4]*aMatrix.myMatrix[0] + myMatrix[5]*aMatrix.myMatrix[4] + myMatrix[6]*aMatrix.myMatrix[8] + myMatrix[7]*aMatrix.myMatrix[12];
	matrix.myMatrix[5]  = myMatrix[4]*aMatrix.myMatrix[1] + myMatrix[5]*aMatrix.myMatrix[5] + myMatrix[6]*aMatrix.myMatrix[9] + myMatrix[7]*aMatrix.myMatrix[13];
	matrix.myMatrix[6]  = myMatrix[4]*aMatrix.myMatrix[2] + myMatrix[5]*aMatrix.myMatrix[6] + myMatrix[6]*aMatrix.myMatrix[10] + myMatrix[7]*aMatrix.myMatrix[14];
	matrix.myMatrix[7]  = myMatrix[4]*aMatrix.myMatrix[3] + myMatrix[5]*aMatrix.myMatrix[7] + myMatrix[6]*aMatrix.myMatrix[11] + myMatrix[7]*aMatrix.myMatrix[15];

	matrix.myMatrix[8]  = myMatrix[8]*aMatrix.myMatrix[0] + myMatrix[9]*aMatrix.myMatrix[4] + myMatrix[10]*aMatrix.myMatrix[8] + myMatrix[11]*aMatrix.myMatrix[12];
	matrix.myMatrix[9]  = myMatrix[8]*aMatrix.myMatrix[1] + myMatrix[9]*aMatrix.myMatrix[5] + myMatrix[10]*aMatrix.myMatrix[9] + myMatrix[11]*aMatrix.myMatrix[13];
	matrix.myMatrix[10] = myMatrix[8]*aMatrix.myMatrix[2] + myMatrix[9]*aMatrix.myMatrix[6] + myMatrix[10]*aMatrix.myMatrix[10] + myMatrix[11]*aMatrix.myMatrix[14];
	matrix.myMatrix[11] = myMatrix[8]*aMatrix.myMatrix[3] + myMatrix[9]*aMatrix.myMatrix[7] + myMatrix[10]*aMatrix.myMatrix[11] + myMatrix[11]*aMatrix.myMatrix[15];

	matrix.myMatrix[12] = myMatrix[12]*aMatrix.myMatrix[0] + myMatrix[13]*aMatrix.myMatrix[4] + myMatrix[14]*aMatrix.myMatrix[8] + myMatrix[15]*aMatrix.myMatrix[12];
	matrix.myMatrix[13] = myMatrix[12]*aMatrix.myMatrix[1] + myMatrix[13]*aMatrix.myMatrix[5] + myMatrix[14]*aMatrix.myMatrix[9] + myMatrix[15]*aMatrix.myMatrix[13];
	matrix.myMatrix[14] = myMatrix[12]*aMatrix.myMatrix[2] + myMatrix[13]*aMatrix.myMatrix[6] + myMatrix[14]*aMatrix.myMatrix[10] + myMatrix[15]*aMatrix.myMatrix[14];
	matrix.myMatrix[15] = myMatrix[12]*aMatrix.myMatrix[3] + myMatrix[13]*aMatrix.myMatrix[7] + myMatrix[14]*aMatrix.myMatrix[11] + myMatrix[15]*aMatrix.myMatrix[15];
	
	return matrix;
}

template <class Type>
Matrix44<Type> Matrix44<Type>::operator+(const Matrix44<Type> &aMatrix) const
{
	Matrix44<Type> matrix;

	for (int index = 0; index < ourSize; index++)
	{
		matrix.myMatrix[index] = myMatrix[index] + aMatrix.myMatrix[index];
	}

	return matrix;
}

template <class Type>
Matrix44<Type> Matrix44<Type>::operator-(const Matrix44<Type> &aMatrix) const
{
	Matrix44<Type> matrix;

	for (int index = 0; index < ourSize; index++)
	{
		matrix.myMatrix[index] = myMatrix[index] - aMatrix.myMatrix[index];
	}

	return matrix;
}

template <class Type>
Matrix44<Type> Matrix44<Type>::CreateRotateAroundX(Type aAngleInRadians)
{
	Matrix44<Type> matrix;
	
	matrix.myMatrix[0] = 1;
	matrix.myMatrix[5] = cos(aAngleInRadians);
	matrix.myMatrix[6] = sin(aAngleInRadians);
	matrix.myMatrix[9] = -sin(aAngleInRadians);
	matrix.myMatrix[10] = cos(aAngleInRadians);

	return matrix;
}

template <class Type>
Matrix33<Type> Matrix44<Type>::Get33() const
{
	Matrix33<Type> matrix;

	matrix.myMatrix[0] = myMatrix[0];
	matrix.myMatrix[1] = myMatrix[1];
	matrix.myMatrix[2] = myMatrix[2];

	matrix.myMatrix[3] = myMatrix[4];
	matrix.myMatrix[4] = myMatrix[5];
	matrix.myMatrix[5] = myMatrix[6];

	matrix.myMatrix[6] = myMatrix[8];
	matrix.myMatrix[7] = myMatrix[9];
	matrix.myMatrix[8] = myMatrix[10];

	return matrix;
}

template <class Type>
void Matrix44<Type>::Set33(const Matrix33<Type> &aMatrix33)
{
	myMatrix[0] = aMatrix33.myMatrix[0];
	myMatrix[1] = aMatrix33.myMatrix[1];
	myMatrix[2] = aMatrix33.myMatrix[2];
	myMatrix[3] = 0;

	myMatrix[4] = aMatrix33.myMatrix[3];
	myMatrix[5] = aMatrix33.myMatrix[4];
	myMatrix[6] = aMatrix33.myMatrix[5];
	myMatrix[7] = 0;

	myMatrix[8] = aMatrix33.myMatrix[6];
	myMatrix[9] = aMatrix33.myMatrix[7];
	myMatrix[10] = aMatrix33.myMatrix[8];
	myMatrix[11] = 0;
}

template <class Type>
void Matrix44<Type>::SetPosition(const Vector3<Type> &aPosition)
{
	myMatrix[12] = aPosition.myX;
	myMatrix[13] = aPosition.myY;
	myMatrix[14] = aPosition.myZ;
}

template <class Type>
Vector3<Type> Matrix44<Type>::GetPosition() const

{
	Vector3<Type> position;

	position.myX = myMatrix[12];
	position.myY = myMatrix[13];
	position.myZ = myMatrix[14];

	return position;
}

template <class Type>
Matrix44<Type> Matrix44<Type>::CreateRotateAroundY(Type aAngleInRadians)
{
	Matrix44<Type> matrix;

	matrix.myMatrix[0] = cos(aAngleInRadians);
	matrix.myMatrix[2] = -sin(aAngleInRadians);
	matrix.myMatrix[5] = 1;
	matrix.myMatrix[8] = sin(aAngleInRadians);
	matrix.myMatrix[10] = cos(aAngleInRadians);

	return matrix;
}

template <class Type>
Matrix44<Type> Matrix44<Type>::CreateRotateAroundZ(Type aAngleInRadians)
{
	Matrix44<Type> matrix;

	matrix.myMatrix[0] = cos(aAngleInRadians);
	matrix.myMatrix[1] = sin(aAngleInRadians);
	matrix.myMatrix[4] = -sin(aAngleInRadians);
	matrix.myMatrix[5] = cos(aAngleInRadians);
	matrix.myMatrix[10] = 1;

	return matrix;
}

template <class Type>
Matrix44<Type> Matrix44<Type>::Inverse() const
{
	Matrix33<Type> invOrientation = Get33().Inverse();
	Vector3<Type> invPosition = (GetPosition() * -1) * invOrientation;

	Matrix44<Type> matrix;

	matrix.myMatrix[0] = invOrientation.myMatrix[0];
	matrix.myMatrix[1] = invOrientation.myMatrix[1];
	matrix.myMatrix[2] = invOrientation.myMatrix[2];
	matrix.myMatrix[3] = 0;

	matrix.myMatrix[4] = invOrientation.myMatrix[3];
	matrix.myMatrix[5] = invOrientation.myMatrix[4];
	matrix.myMatrix[6] = invOrientation.myMatrix[5];
	matrix.myMatrix[7] = 0;

	matrix.myMatrix[8] = invOrientation.myMatrix[6];
	matrix.myMatrix[9] = invOrientation.myMatrix[7];
	matrix.myMatrix[10] = invOrientation.myMatrix[8];
	matrix.myMatrix[11] = 0;
	
	matrix.SetPosition(invPosition);
	matrix.myMatrix[15] = 1;

	return matrix;
}

template <class Type>
Matrix44<Type> Matrix44<Type>::TransposeInverse() const
{
	Matrix33<Type> invertedMatrix;
	invertedMatrix.myMatrix[0] = myMatrix[0];
	invertedMatrix.myMatrix[1] = myMatrix[4];
	invertedMatrix.myMatrix[2] = myMatrix[8];

	invertedMatrix.myMatrix[3] = myMatrix[1];
	invertedMatrix.myMatrix[4] = myMatrix[5];
	invertedMatrix.myMatrix[5] = myMatrix[9];

	invertedMatrix.myMatrix[6] = myMatrix[2];
	invertedMatrix.myMatrix[7] = myMatrix[6];
	invertedMatrix.myMatrix[8] = myMatrix[10];

	Vector3<Type> invPosition = (GetPosition() * -1) * invertedMatrix;

	Matrix44f returnMatrix;
	returnMatrix.SetPosition(invPosition);
	returnMatrix.Set33(invertedMatrix);
	return returnMatrix;
}

template <class Type>
void Matrix44<Type>::NormalizeIndividualVectors()
{
	Vector4<Type> xVec = GetXVector().Normalize();
	Vector4<Type> yVec = GetYVector().Normalize();
	Vector4<Type> zVec = GetZVector().Normalize();

	myMatrix[0] = xVec.x;
	myMatrix[1] = xVec.y;
	myMatrix[2] = xVec.z;
	myMatrix[3] = xVec.w;

	myMatrix[4] = yVec.x;
	myMatrix[5] = yVec.y;
	myMatrix[6] = yVec.z;
	myMatrix[7] = yVec.w;

	myMatrix[8] = zVec.x;
	myMatrix[9] = zVec.y;
	myMatrix[10] = zVec.z;
	myMatrix[11] = zVec.w;
}

template <class Type>
Vector4<Type> Matrix44<Type>::GetXVector()
{
	Vector4<Type> vector;
	vector.x = myMatrix[0];
	vector.y = myMatrix[1];
	vector.z = myMatrix[2];
	vector.w = myMatrix[3];

	return vector;
}

template <class Type>
Vector4<Type> Matrix44<Type>::GetYVector()
{
	Vector4<Type> vector;
	vector.x = myMatrix[4];
	vector.y = myMatrix[5];
	vector.z = myMatrix[6];
	vector.w = myMatrix[7];

	return vector;
}

template <class Type>
Vector4<Type> Matrix44<Type>::GetZVector()
{
	Vector4<Type> vector;
	vector.x = myMatrix[8];
	vector.y = myMatrix[9];
	vector.z = myMatrix[10];
	vector.w = myMatrix[11];

	return vector;
}

template<typename Type>
void Matrix44<Type>::operator =(D3DXMATRIX aMatrix)
{
	for(int index = 0; index < 16; index++)
	{
		myMatrix[index] = aMatrix[index];
	}
}

template <class Type>
class Matrix33
{
public:
	Matrix33();
	Matrix33(const Matrix44<Type> &aMatrix);
	~Matrix33();

	Matrix33<Type> operator+(const Matrix33<Type> &aMatrix) const;
	Matrix33<Type> operator-(const Matrix33<Type> &aMatrix) const;
	Matrix33<Type> operator*(const Matrix33<Type> &aMatrix) const;
	Matrix33<Type> operator*(const Matrix44<Type> &aMatrix) const;
	Matrix33<Type>& operator*=(const Matrix33<Type> &aMatrix);
	Matrix33<Type>& operator=(const Matrix33<Type> &aMatrix);
	bool operator==(const Matrix33<Type> &aMatrix) const;

	static Matrix33<Type> CreateRotateAroundX(Type aAngleInRadians);
	static Matrix33<Type> CreateRotateAroundY(Type aAngleInRadians);
	static Matrix33<Type> CreateRotateAroundZ(Type aAngleInRadians);
	static Matrix33<Type> Identity();
	static Matrix33<Type> RotationAroundVector(Vector3<float> aVector,float aNumber);

	Type Determinant() const;
	Matrix33<Type> Inverse() const;
public:
	static const int ourSize = 9;
	Type myMatrix[ourSize];
};

template <class Type>
Matrix33<Type>::Matrix33()
{
	myMatrix[0] = 1;
	myMatrix[1] = 0;
	myMatrix[2] = 0;

	myMatrix[3] = 0;
	myMatrix[4] = 1;
	myMatrix[5] = 0;

	myMatrix[6] = 0;
	myMatrix[7] = 0;
	myMatrix[8] = 1;
}

template <class Type>
Matrix33<Type>::Matrix33(const Matrix44<Type> &aMatrix)
{
	myMatrix[0] = aMatrix.myMatrix[0];
	myMatrix[1] = aMatrix.myMatrix[1];
	myMatrix[2] = aMatrix.myMatrix[2];

	myMatrix[3] = aMatrix.myMatrix[4];
	myMatrix[4] = aMatrix.myMatrix[5];
	myMatrix[5] = aMatrix.myMatrix[6];

	myMatrix[6] = aMatrix.myMatrix[8];
	myMatrix[7] = aMatrix.myMatrix[9];
	myMatrix[8] = aMatrix.myMatrix[10];
}

template <class Type>
Matrix33<Type>::~Matrix33()
{

}

template <class Type>
Matrix33<Type> Matrix33<Type>::Identity()
{
	Matrix33<Type> matrix;

	matrix.myMatrix[0] = 1;
	matrix.myMatrix[1] = 0;
	matrix.myMatrix[2] = 0;

	matrix.myMatrix[3] = 0;
	matrix.myMatrix[4] = 1;
	matrix.myMatrix[5] = 0;

	matrix.myMatrix[6] = 0;
	matrix.myMatrix[7] = 0;
	matrix.myMatrix[8] = 1;

	return matrix;
}

template <class Type>
bool Matrix33<Type>::operator==(const Matrix33<Type> &aMatrix) const
{
	for (int index = 0; index < ourSize; index++)
	{
		if ((myMatrix[index] == aMatrix.myMatrix[index]) == false)
		{
			return false;
		}
	}
	return true;
}

template <class Type>
Matrix33<Type>& Matrix33<Type>::operator=(const Matrix33<Type> &aMatrix)
{
	for (int index = 0; index < ourSize; index++)
	{
		myMatrix[index] = aMatrix.myMatrix[index];
	}
	return (*this);
}

template <class Type>
Matrix33<Type>& Matrix33<Type>::operator*=(const Matrix33<Type> &aMatrix)
{
	Type matrix[ourSize];

	matrix[0] = myMatrix[0]*aMatrix.myMatrix[0] + myMatrix[1]*aMatrix.myMatrix[3] + myMatrix[2]*aMatrix.myMatrix[6];
	matrix[1] = myMatrix[0]*aMatrix.myMatrix[1] + myMatrix[1]*aMatrix.myMatrix[4] + myMatrix[2]*aMatrix.myMatrix[7];
	matrix[2] = myMatrix[0]*aMatrix.myMatrix[2] + myMatrix[1]*aMatrix.myMatrix[5] + myMatrix[2]*aMatrix.myMatrix[8];

	matrix[3] = myMatrix[3]*aMatrix.myMatrix[0] + myMatrix[4]*aMatrix.myMatrix[3] + myMatrix[5]*aMatrix.myMatrix[6];
	matrix[4] = myMatrix[3]*aMatrix.myMatrix[1] + myMatrix[4]*aMatrix.myMatrix[4] + myMatrix[5]*aMatrix.myMatrix[7];
	matrix[5] = myMatrix[3]*aMatrix.myMatrix[2] + myMatrix[4]*aMatrix.myMatrix[5] + myMatrix[5]*aMatrix.myMatrix[8];

	matrix[6] = myMatrix[6]*aMatrix.myMatrix[0] + myMatrix[7]*aMatrix.myMatrix[3] + myMatrix[8]*aMatrix.myMatrix[6];
	matrix[7] = myMatrix[6]*aMatrix.myMatrix[1] + myMatrix[7]*aMatrix.myMatrix[4] + myMatrix[8]*aMatrix.myMatrix[7];
	matrix[8] = myMatrix[6]*aMatrix.myMatrix[2] + myMatrix[7]*aMatrix.myMatrix[5] + myMatrix[8]*aMatrix.myMatrix[8];

	for (int index = 0; index < ourSize; index++)
	{
		myMatrix[index] = matrix[index];
	}

	return (*this);
}

template <class Type>
Matrix33<Type> Matrix33<Type>::operator*(const Matrix44<Type> &aMatrix) const
{
	Matrix33<Type> matrix;

	matrix.myMatrix[0] = (myMatrix[0] * aMatrix.myMatrix[0]) + (myMatrix[1] * aMatrix.myMatrix[4]) + (myMatrix[2] * aMatrix.myMatrix[8]);
	matrix.myMatrix[1] = (myMatrix[0] * aMatrix.myMatrix[1]) + (myMatrix[1] * aMatrix.myMatrix[5]) + (myMatrix[2] * aMatrix.myMatrix[9]);
	matrix.myMatrix[2] = (myMatrix[0] * aMatrix.myMatrix[2]) + (myMatrix[1] * aMatrix.myMatrix[6]) + (myMatrix[2] * aMatrix.myMatrix[10]);

	matrix.myMatrix[0] = (myMatrix[3] * aMatrix.myMatrix[0]) + (myMatrix[4] * aMatrix.myMatrix[4]) + (myMatrix[5] * aMatrix.myMatrix[8]);
	matrix.myMatrix[1] = (myMatrix[3] * aMatrix.myMatrix[1]) + (myMatrix[4] * aMatrix.myMatrix[5]) + (myMatrix[5] * aMatrix.myMatrix[9]);
	matrix.myMatrix[2] = (myMatrix[3] * aMatrix.myMatrix[2]) + (myMatrix[4] * aMatrix.myMatrix[6]) + (myMatrix[5] * aMatrix.myMatrix[10]);

	matrix.myMatrix[0] = (myMatrix[6] * aMatrix.myMatrix[0]) + (myMatrix[7] * aMatrix.myMatrix[4]) + (myMatrix[8] * aMatrix.myMatrix[8]);
	matrix.myMatrix[1] = (myMatrix[6] * aMatrix.myMatrix[1]) + (myMatrix[7] * aMatrix.myMatrix[5]) + (myMatrix[8] * aMatrix.myMatrix[9]);
	matrix.myMatrix[2] = (myMatrix[6] * aMatrix.myMatrix[2]) + (myMatrix[7] * aMatrix.myMatrix[6]) + (myMatrix[8] * aMatrix.myMatrix[10]);

	return matrix;
}

template <class Type>
Matrix33<Type> Matrix33<Type>::operator*(const Matrix33<Type> &aMatrix) const
{
	Matrix33<Type> matrix;

	matrix.myMatrix[0] = myMatrix[0]*aMatrix.myMatrix[0] + myMatrix[1]*aMatrix.myMatrix[3] + myMatrix[2]*aMatrix.myMatrix[6];
	matrix.myMatrix[1] = myMatrix[0]*aMatrix.myMatrix[1] + myMatrix[1]*aMatrix.myMatrix[4] + myMatrix[2]*aMatrix.myMatrix[7];
	matrix.myMatrix[2] = myMatrix[0]*aMatrix.myMatrix[2] + myMatrix[1]*aMatrix.myMatrix[5] + myMatrix[2]*aMatrix.myMatrix[8];

	matrix.myMatrix[3] = myMatrix[3]*aMatrix.myMatrix[0] + myMatrix[4]*aMatrix.myMatrix[3] + myMatrix[5]*aMatrix.myMatrix[6];
	matrix.myMatrix[4] = myMatrix[3]*aMatrix.myMatrix[1] + myMatrix[4]*aMatrix.myMatrix[4] + myMatrix[5]*aMatrix.myMatrix[7];
	matrix.myMatrix[5] = myMatrix[3]*aMatrix.myMatrix[2] + myMatrix[4]*aMatrix.myMatrix[5] + myMatrix[5]*aMatrix.myMatrix[8];

	matrix.myMatrix[6] = myMatrix[6]*aMatrix.myMatrix[0] + myMatrix[7]*aMatrix.myMatrix[3] + myMatrix[8]*aMatrix.myMatrix[6];
	matrix.myMatrix[7] = myMatrix[6]*aMatrix.myMatrix[1] + myMatrix[7]*aMatrix.myMatrix[4] + myMatrix[8]*aMatrix.myMatrix[7];
	matrix.myMatrix[8] = myMatrix[6]*aMatrix.myMatrix[2] + myMatrix[7]*aMatrix.myMatrix[5] + myMatrix[8]*aMatrix.myMatrix[8];

	return matrix;
}

template <class Type>
Matrix33<Type> Matrix33<Type>::operator+(const Matrix33<Type> &aMatrix) const
{
	Matrix33<Type> matrix;

	for (int index = 0; index < ourSize; index++)
	{
		matrix.myMatrix[index] = myMatrix[index] + aMatrix.myMatrix[index];
	}

	return matrix;
}

template <class Type>
Matrix33<Type> Matrix33<Type>::operator-(const Matrix33<Type> &aMatrix) const
{
	Matrix33<Type> matrix;

	for (int index = 0; index < ourSize; index++)
	{
		matrix.myMatrix[index] = myMatrix[index] - aMatrix.myMatrix[index];
	}

	return matrix;
}

template <class Type>
Matrix33<Type> Matrix33<Type>::CreateRotateAroundX(Type aAngleInRadians)
{
	Matrix33<Type> matrix;
	
	for (int index = 0; index < ourSize; index++)
	{
		matrix.myMatrix[index] = 0;
	}

	matrix.myMatrix[0] = 1;
	matrix.myMatrix[4] = cos(aAngleInRadians);
	matrix.myMatrix[5] = sin(aAngleInRadians);
	matrix.myMatrix[7] = -sin(aAngleInRadians);
	matrix.myMatrix[8] = cos(aAngleInRadians);

	return matrix;
}

template <class Type>
Matrix33<Type> Matrix33<Type>::CreateRotateAroundY(Type aAngleInRadians)
{
	Matrix33<Type> matrix;
	
	for (int index = 0; index < ourSize; index++)
	{
		matrix.myMatrix[index] = 0;
	}

	matrix.myMatrix[0] = cos(aAngleInRadians);
	matrix.myMatrix[2] = -sin(aAngleInRadians);
	matrix.myMatrix[4] = 1;
	matrix.myMatrix[6] = sin(aAngleInRadians);
	matrix.myMatrix[8] = cos(aAngleInRadians);

	return matrix;
}

template <class Type>
Matrix33<Type> Matrix33<Type>::CreateRotateAroundZ(Type aAngleInRadians)
{
	Matrix33<Type> matrix;
	
	for (int index = 0; index < ourSize; index++)
	{
		matrix.myMatrix[index] = 0;
	}

	matrix.myMatrix[0] = cos(aAngleInRadians);
	matrix.myMatrix[1] = sin(aAngleInRadians);
	matrix.myMatrix[3] = -sin(aAngleInRadians);
	matrix.myMatrix[4] = cos(aAngleInRadians);
	matrix.myMatrix[8] = 1;

	return matrix;
}
template <class Type>
Matrix33<Type> Matrix33<Type>::RotationAroundVector(Vector3<float> aVector,float aNumber)
{
  Matrix33<Type> zRotationMatrix;

  zRotationMatrix.myMatrix[0] = static_cast<float>( (aVector.x * aVector.x) * ( 1 - cos(static_cast<float>(aNumber)) )  + static_cast<float>(cos(aNumber)) );
  zRotationMatrix.myMatrix[1] = static_cast<float>( (aVector.x * aVector.y) * ( 1 - cos(static_cast<float>(aNumber)) ) + ( aVector.z * sin(static_cast<float>(aNumber)) ) );
  zRotationMatrix.myMatrix[2] = static_cast<float>( (aVector.x * aVector.z) * ( 1 - cos(static_cast<float>(aNumber)) ) - ( aVector.y * sin(static_cast<float>(aNumber)) ) );
  zRotationMatrix.myMatrix[3] = static_cast<float>( (aVector.x * aVector.y) * ( 1 - cos(static_cast<float>(aNumber)) ) - ( aVector.z * sin(static_cast<float>(aNumber)) ) );
  zRotationMatrix.myMatrix[4] = static_cast<float>( (aVector.y * aVector.y) * ( 1 - cos(static_cast<float>(aNumber)) ) + cos(static_cast<float>(aNumber)) );
  zRotationMatrix.myMatrix[5] = static_cast<float>( (aVector.y * aVector.z) * ( 1 - cos(static_cast<float>(aNumber)) ) + ( aVector.x * sin(static_cast<float>(aNumber)) ) );
  zRotationMatrix.myMatrix[6] = static_cast<float>( (aVector.x * aVector.z) * ( 1 - cos(static_cast<float>(aNumber)) ) + ( aVector.y * sin(static_cast<float>(aNumber)) ) );
  zRotationMatrix.myMatrix[7] = static_cast<float>( (aVector.y * aVector.z) * ( 1 - cos(static_cast<float>(aNumber)) ) - ( aVector.x * sin(static_cast<float>(aNumber)) ) );
  zRotationMatrix.myMatrix[8] = static_cast<float>( (aVector.z * aVector.z) * ( 1 - cos(static_cast<float>(aNumber)) ) + cos(static_cast<float>(aNumber)) );

  return zRotationMatrix;
}
template <class Type>
Type Matrix33<Type>::Determinant() const
{
	const Vector3<Type> a(myMatrix[0],myMatrix[1],myMatrix[2]);
	const Vector3<Type> b(myMatrix[3],myMatrix[4],myMatrix[5]);
	const Vector3<Type> c(myMatrix[6],myMatrix[7],myMatrix[8]);
	return a.Cross(b).Normalize().Dot(c.Normalize());
}

template <class Type>
Matrix33<Type> Matrix33<Type>::Inverse() const
{
	const Type determinant = Determinant();

	Matrix33<Type> matrix;

	matrix.myMatrix[0] = myMatrix[0] / determinant;
	matrix.myMatrix[1] = myMatrix[3] / determinant;
	matrix.myMatrix[2] = myMatrix[6] / determinant;

	matrix.myMatrix[3] = myMatrix[1] / determinant;
	matrix.myMatrix[4] = myMatrix[4] / determinant;
	matrix.myMatrix[5] = myMatrix[7] / determinant;

	matrix.myMatrix[6] = myMatrix[2] / determinant;
	matrix.myMatrix[7] = myMatrix[5] / determinant;
	matrix.myMatrix[8] = myMatrix[8] / determinant;

	return matrix;
}



typedef Matrix44<float> Matrix44f;
typedef Matrix33<float> Matrix33f;

#endif