#ifndef _ORIENTATION_H_
#define _ORIENTATION_H_
#include "Matrix.h"

template <class Type>
class Orientation
{
public:
	Orientation();
	~Orientation();
	void SetPosition(const Vector3<Type> &aPosition);
	Vector3<Type> GetPosition() const;

	Matrix33<Type> GetRotation() const;
	void SetRotation(const Matrix33<Type> &aRotation);
	void SetTransformation(const Matrix44<Type> &aTransformation);

	void Rotate(Matrix33<Type> aRotation);
	void Transform(Matrix44<Type> aTransformation);
	void Translate(const Vector3<Type> &aTranslation);

	Orientation<Type> operator*(const Orientation<Type> &aMatrix) const;
	Orientation<Type> Inverse() const;
private:
	Matrix44<Type> myMatrix;
};

template <class Type>
Orientation<Type>::Orientation()
{

}

template <class Type>
Orientation<Type>::~Orientation()
{

}

template <class Type>
void Orientation<Type>::SetPosition(const Vector3<Type> &aPosition)
{
	myMatrix.SetPosition(aPosition);
}

template <class Type>
Vector3<Type> Orientation<Type>::GetPosition() const
{
	return myMatrix.GetPosition();
}

template <class Type>
Matrix33<Type> Orientation<Type>::GetRotation() const
{
	return myMatrix.Get33();
}

template <class Type>
void Orientation<Type>::SetRotation(const Matrix33<Type> &aRotation)
{
	myMatrix.Set33(aRotation);
}

template <class Type>
void Orientation<Type>::SetTransformation(const Matrix44<Type> &aTransformation)
{
	myMatrix = aTransformation;
}

template <class Type>
void Orientation<Type>::Rotate(Matrix33<Type> aRotation)
{
	SetRotation(aRotation * myMatrix.Get33());
}

template <class Type>
void Orientation<Type>::Transform(Matrix44<Type> aTransformation)
{
	myMatrix = aTransformation * myMatrix;
}

template <class Type>
void Orientation<Type>::Translate(const Vector3<Type> &aTranslation)
{
	Vector3<Type> newPosition = aTranslation * myMatrix.Get33();
	myMatrix.SetPosition(myMatrix.GetPosition() + newPosition);
}

template <class Type>
Orientation<Type> Orientation<Type>::operator*(const Orientation<Type> &aMatrix) const
{
	Orientation<Type> orientation;
	orientation.myMatrix = myMatrix * aMatrix.myMatrix;
	return orientation;
}

template <class Type>
Orientation<Type> Orientation<Type>::Inverse() const
{
	Orientation<Type> orientation;
	orientation.myMatrix = myMatrix.Inverse();
	return orientation;
}

#endif