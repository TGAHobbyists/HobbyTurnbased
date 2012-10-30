#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <math.h>

template <class Type> class Matrix33;
template <class Type> class Matrix44;

template <class Type>
class Vector2
{
public:
	inline Vector2();
	inline Vector2(Type aX, Type aY);
	inline ~Vector2();
	inline Vector2<Type> operator+(const Vector2<Type> &aVector) const;
	inline Vector2<Type> operator-(const Vector2<Type> &aVector) const;
	inline Vector2<Type> operator*(const Type aTypeValue) const;
	inline Vector2<Type> operator*(const Vector2<Type> &aVector) const;
	inline Vector2<Type> operator/(const Type aTypeValue) const;
	inline Vector2<Type> operator/(const Vector2<Type> &aVector) const;
	inline Vector2<Type>& operator+=(const Vector2<Type> &aVector);
	inline Vector2<Type>& operator-=(const Vector2<Type> &aVector);
	inline Vector2<Type>& operator*=(const Vector2<Type> &aVector);
	inline Vector2<Type>& operator/=(const Vector2<Type> &aVector);
	inline bool operator==(const Vector2<Type> &aVector) const;
	inline bool operator!=(const Vector2<Type> &aVector) const;
	inline bool operator!=(Type aType) const;
	inline bool operator>(const Type aType) const;
	inline bool operator<(const Type aType) const;

	inline float Length() const;
	inline float Length2() const;
	inline Vector2<Type> Rotate(float aRotation);
	inline Type Dot(const Vector2<Type> &aVector) const;
	inline Vector2<Type> Normalize() const;
	inline void Set(Type aX, Type anY);
public:
	union
	{
		Type       myX;
		Type       x;
		Type       r;
		Type       U;
		Type       myR;
		Type       myU;
	};
	union
	{
		Type       myY;
		Type       y;
		Type       g;
		Type       v;
		Type       myG;
		Type       myV;
	};
};

template <class Type>
Vector2<Type>::Vector2()
{
	myX = 0;
	myY	= 0;
}


template <class Type>
Vector2<Type>::Vector2(Type aX, Type aY)
{
	myX = aX;
	myY	= aY;
}

template <class Type>
Vector2<Type>::~Vector2()
{

}

template <class Type>
Vector2<Type> Vector2<Type>::operator+(const Vector2<Type> &aVector) const
{
	Vector2<Type> sum;
	sum.myX = myX + aVector.myX;
	sum.myY = myY + aVector.myY;
	return sum;
}

template <class Type>
Vector2<Type> Vector2<Type>::operator-(const Vector2<Type> &aVector) const
{
	Vector2<Type> sum;
	sum.myX = myX - aVector.myX;
	sum.myY = myY - aVector.myY;
	return sum;
}

template <class Type>
Vector2<Type> Vector2<Type>::operator*(const Type aTypeValue) const
{
	Vector2<Type> sum;
	sum.myX = myX * aTypeValue;
	sum.myY = myY * aTypeValue;
	return sum;
}

template <class Type>
Vector2<Type> Vector2<Type>::operator*(const Vector2<Type> &aVector) const
{
	Vector2<Type> sum;
	sum.myX = myX * aVector.myX;
	sum.myY = myY * aVector.myY;
	return sum;
}

template <class Type>
Vector2<Type> Vector2<Type>::operator/(const Vector2<Type> &aVector) const
{
	Vector2<Type> sum;
	sum.myX = myX / aVector.myX;
	sum.myY = myY / aVector.myY;
	return sum;
}

template <class Type>
Vector2<Type> Vector2<Type>::operator/(const Type aTypeValue) const
{
	Vector2<Type> sum;
	sum.myX = myX / aTypeValue;
	sum.myY = myY / aTypeValue;
	return sum;
}

template <class Type>
Vector2<Type>& Vector2<Type>::operator+=(const Vector2<Type> &aVector)
{
	myX += aVector.myX;
	myY += aVector.myY;

	return (*this);
}

template <class Type>
Vector2<Type>& Vector2<Type>::operator-=(const Vector2<Type> &aVector)
{
	myX -= aVector.myX;
	myY -= aVector.myY;

	return (*this);
}

template <class Type>
Vector2<Type>& Vector2<Type>::operator*=(const Vector2<Type> &aVector)
{
	myX *= aVector.myX;
	myY *= aVector.myY;

	return (*this);
}

template <class Type>
Vector2<Type>& Vector2<Type>::operator/=(const Vector2<Type> &aVector)
{
	myX /= aVector.myX;
	myY /= aVector.myY;

	return (*this);
}

template <class Type>
bool Vector2<Type>::operator==(const Vector2<Type> &aVector) const
{
	if (myX == aVector.myX)
	{
		if(myY == aVector.myY)
		{
			return true;
		}
	}
	return false;
}
template <class Type>
bool Vector2<Type>::operator!=(const Vector2<Type> &aVector) const
{
	if( myX == aVector.myX )
	{
		if( myY == aVector.myY )
		{
			return false;
		}
	}
	return true;
}


template <class Type>
bool Vector2<Type>::operator!=( Type aType ) const
{
	if( myX == aType )
	{
		if( myY == aType )
		{
			return false;
		}
	}
	return true;}


template <class Type>
bool Vector2<Type>::operator>( const Type aType ) const
{
	if( myX > aType && myY > aType )
	{
		return true;
	}
	return false;
}


template <class Type>
bool Vector2<Type>::operator<( const Type aType ) const
{
	if( myX < aType && myY < aType )
	{
		return true;
	}
	return false;
}

template <class Type>
float Vector2<Type>::Length() const
{
	return(sqrt((myX*myX) + (myY*myY)));
}

template <class Type>
float Vector2<Type>::Length2() const
{
	return(myX*myX) + (myY*myY);
}

template <class Type>
Vector2<Type> Vector2<Type>::Rotate(float aRotation)
{
	float xrotated = myX * cos(aRotation) + myY * sin(aRotation);
	float yrotated = myY * cos(aRotation) - myX * sin(aRotation);
	return Vector2<Type>(xrotated, yrotated);
}

template <class Type>
Type Vector2<Type>::Dot(const Vector2<Type> &aVector) const
{
	return(myX * aVector.myX + myY * aVector.myY);
}

template <class Type>
Vector2<Type> Vector2<Type>::Normalize() const
{
	float length = Length();
	if(length == 0) return Vector2f();
	return Vector2<Type>(myX/length, myY/length);
}

template <class Type>
void Vector2<Type>::Set(Type aX, Type anY)
{
	myX = aX;
	myY = anY;
}

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

template <class Type>
class Vector3
{
public:
	inline Vector3();
	inline Vector3(Type aX, Type aY, Type aZ);
	inline Vector3(Vector2<Type> aVector2, Type aZValue);
	inline ~Vector3();
	inline Vector3<Type> operator+(const Vector3<Type> &aVector) const;
	inline Vector3<Type> operator-(const Vector3<Type> &aVector) const;
	inline Vector3<Type> operator*(const Type aTypeValue) const;
	inline Vector3<Type> operator*(const Vector3<Type> &aVector) const;
	inline Vector3<Type> operator*(const Matrix33<Type> &aMatrix) const;
	inline Vector3<Type> operator/(const Type aTypeValue) const;
	inline Vector3<Type> operator/(const Vector3<Type> &aVector) const;
	inline Vector3<Type>& operator+=(const Vector3<Type> &aVector);
	inline Vector3<Type>& operator-=(const Vector3<Type> &aVector);
	inline Vector3<Type>& operator*=(const Vector3<Type> &aVector);
	inline Vector3<Type>& operator/=(const Vector3<Type> &aVector);
	inline bool operator==(const Vector3<Type> &aVector) const;
	inline float Length() const;
	inline float Length2() const;
	inline Type Dot(const Vector3<Type> &aVector) const;
	inline Vector3<Type> Cross(const Vector3<Type> &aVector) const;
	inline Vector3<Type> Interpolate(const Vector3<Type> &aRightHandVector, const Vector3<Type> &aLerpValues) const;
	inline void Set(Type aX, Type anY, Type aZ);

	inline Vector3<Type> Normalize() const;
public:
	union
	{
		Type       myX;
		Type       x;
		Type       r;
		Type       myR;
	};
	union
	{
		Type       myY;
		Type       y;
		Type       g;
		Type       myG;
	};
	union
	{
		Type       myZ;
		Type       z;
		Type       b;
		Type       myB;
	};
};

template <class Type>
Vector3<Type>::Vector3()
{
	myX = 0;
	myY	= 0;
	myZ = 0;
}


template <class Type>
Vector3<Type>::Vector3(Type aX, Type aY, Type aZ)
{
	myX = aX;
	myY	= aY;
	myZ = aZ;
}

template <class Type>
Vector3<Type>::Vector3( Vector2<Type> aVector2, Type aZValue )
{
	myX = aVector2.myX;
	myY = aVector2.myY;
	myZ = aZValue;
}

template <class Type>
Vector3<Type>::~Vector3()
{

}

template <class Type>
Vector3<Type> Vector3<Type>::operator+(const Vector3<Type> &aVector) const
{
	Vector3<Type> sum;
	sum.myX = myX + aVector.myX;
	sum.myY = myY + aVector.myY;
	sum.myZ = myZ + aVector.myZ;
	return sum;
}

template <class Type>
Vector3<Type> Vector3<Type>::operator-(const Vector3<Type> &aVector) const
{
	Vector3<Type> sum;
	sum.myX = myX - aVector.myX;
	sum.myY = myY - aVector.myY;
	sum.myZ = myZ - aVector.myZ;
	return sum;
}

template <class Type>
Vector3<Type> Vector3<Type>::operator*(const Type aTypeValue) const
{
	Vector3<Type> sum;
	sum.myX = myX * aTypeValue;
	sum.myY = myY * aTypeValue;
	sum.myZ = myZ * aTypeValue;
	return sum;
}

template <class Type>
Vector3<Type> Vector3<Type>::operator*(const Vector3<Type> &aVector) const
{
	Vector3<Type> sum;
	sum.myX = myX * aVector.myX;
	sum.myY = myY * aVector.myY;
	sum.myZ = myZ * aVector.myZ;
	return sum;
}

template <class Type>
Vector3<Type> Vector3<Type>::operator*(const Matrix33<Type> &aMatrix) const
{
	Vector3<Type> sum;
	
	sum.myX = (myX*aMatrix.myMatrix[0]) + (myY*aMatrix.myMatrix[3]) + (myZ*aMatrix.myMatrix[6]);
	sum.myY = (myX*aMatrix.myMatrix[1]) + (myY*aMatrix.myMatrix[4]) + (myZ*aMatrix.myMatrix[7]);
	sum.myZ = (myX*aMatrix.myMatrix[2]) + (myY*aMatrix.myMatrix[5]) + (myZ*aMatrix.myMatrix[8]);

	return sum;
}

template <class Type>
Vector3<Type> Vector3<Type>::operator/(const Vector3<Type> &aVector) const
{
	Vector3<Type> sum;
	sum.myX = myX / aVector.myX;
	sum.myY = myY / aVector.myY;
	sum.myZ = myZ / aVector.myZ;
	return sum;
}

template <class Type>
Vector3<Type> Vector3<Type>::operator/(const Type aTypeValue) const
{
	Vector3<Type> sum;
	sum.myX = myX / aTypeValue;
	sum.myY = myY / aTypeValue;
	sum.myZ = myZ / aTypeValue;
	return sum;
}


template <class Type>
Vector3<Type>& Vector3<Type>::operator+=(const Vector3<Type> &aVector)
{
	myX += aVector.myX;
	myY += aVector.myY;
	myZ += aVector.myZ;

	return (*this);
}

template <class Type>
Vector3<Type>& Vector3<Type>::operator-=(const Vector3<Type> &aVector)
{
	myX -= aVector.myX;
	myY -= aVector.myY;
	myZ -= aVector.myZ;
	return (*this);
}

template <class Type>
Vector3<Type>& Vector3<Type>::operator*=(const Vector3<Type> &aVector)
{
	myX *= aVector.myX;
	myY *= aVector.myY;
	myZ *= aVector.myZ;
	return (*this);
}

template <class Type>
Vector3<Type>& Vector3<Type>::operator/=(const Vector3<Type> &aVector)
{
	myX /= aVector.myX;
	myY /= aVector.myY;
	myZ /= aVector.myZ;
	return (*this);
}

template <class Type>
bool Vector3<Type>::operator==(const Vector3<Type> &aVector) const
{
	if (myX == aVector.myX)
	{
		if (myY == aVector.myY)
		{
			if (myZ == aVector.myZ)
			{
				return true;
			}
		}
	}
	return false;
}


template <class Type>
float Vector3<Type>::Length() const
{
	return( sqrt( (myX*myX) + (myY*myY) + (myZ*myZ) ) );
}

template <class Type>
float Vector3<Type>::Length2() const
{
	return( (myX*myX) + (myY*myY) + (myZ*myZ) );
}

template <class Type>
Type Vector3<Type>::Dot(const Vector3<Type> &aVector) const
{
	return(myX * aVector.myX + myY * aVector.myY + myZ * aVector.myZ);
}

template <class Type>
Vector3<Type> Vector3<Type>::Cross(const Vector3<Type> &aVector) const
{
	Vector3<Type> result;
	result.myX = (myY * aVector.myZ) - (myZ * aVector.myY);
	result.myY = (myZ * aVector.myX) - (myX * aVector.myZ);
	result.myZ = (myX * aVector.myY) - (myY * aVector.myX);
	return result;
}

template <class Type>
Vector3<Type> Vector3<Type>::Interpolate( const Vector3<Type> &aRightHandVector, const Vector3<Type> &aLerpValues ) const
{
	Vector3f newVector;
	newVector.myX = myX + (aLerpValues.myX * (aRightHandVector.myX - myX));
	newVector.myY = myY + (aLerpValues.myY * (aRightHandVector.myY - myY));
	newVector.myZ = myZ + (aLerpValues.myZ * (aRightHandVector.myZ - myZ));
	return newVector;
}

template <class Type>
Vector3<Type> Vector3<Type>::Normalize() const
{
	const float length = Length();
	if(length == 0) return *this;
	Vector3<Type> normalizedVector;
	normalizedVector.myX = x / length;
	normalizedVector.myY = y / length;
	normalizedVector.myZ = z / length;
	return normalizedVector;
}

template <class Type>
void Vector3<Type>::Set(Type aX, Type anY, Type aZ)
{
	myX = aX;
	myY = anY;
	myZ = aZ;
}

typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;

template <class Type>
class Vector4
{
public:
	inline Vector4();
	inline Vector4(Type aX, Type aY, Type aZ, Type aW);
	inline ~Vector4();
	inline Vector4<Type> operator+(const Vector4<Type> &aVector) const;
	inline Vector4<Type> operator-(const Vector4<Type> &aVector) const;
	inline Vector4<Type> operator*(const Type aTypeValue) const;
	inline Vector4<Type> operator*(const Vector4<Type> &aVector) const;
	inline Vector4<Type> operator*(const Matrix44<Type> &aMatrix) const;
	inline Vector4<Type> operator/(const Type aTypeValue) const;
	inline Vector4<Type> operator/(const Vector4<Type> &aVector) const;
	inline Vector4<Type>& operator+=(const Vector4<Type> &aVector);
	inline Vector4<Type>& operator-=(const Vector4<Type> &aVector);
	inline Vector4<Type>& operator*=(const Vector4<Type> &aVector);
	inline Vector4<Type>& operator/=(const Vector4<Type> &aVector);
	inline bool operator==(const Vector4 &aVector) const;
	inline float Length() const;
	inline Type Dot(const Vector4<Type> &aVector) const;
	inline Vector3<Type> Vec3() const;
	inline void Set(Type aX, Type anY, Type aZ, Type aW);
public:
	union
	{
		Type       myX;
		Type       x;
		Type       r;
		Type       myR;
	};
	union
	{
		Type       myY;
		Type       y;
		Type       g;
		Type       myG;
	};
	union
	{
		Type       myZ;
		Type       z;
		Type       b;
		Type       myB;
	};
	union
	{
		Type       myW;
		Type       w;
		Type       a;
		Type       myA;
	};
};

template <class Type>
Vector4<Type>::Vector4()
{
	myX = 0;
	myY	= 0;
	myZ = 0;
	myW = 0;
}


template <class Type>
Vector4<Type>::Vector4(Type aX, Type aY, Type aZ, Type aW)
{
	myX = aX;
	myY	= aY;
	myZ = aZ;
	myW = aW;
}

template <class Type>
Vector4<Type>::~Vector4()
{

}

template <class Type>
Vector4<Type> Vector4<Type>::operator+(const Vector4<Type> &aVector) const
{
	Vector4<Type> sum;
	sum.myX = myX + aVector.myX;
	sum.myY = myY + aVector.myY;
	sum.myZ = myZ + aVector.myZ;
	sum.myW = myW + aVector.myW;
	return sum;
}

template <class Type>
Vector4<Type> Vector4<Type>::operator-(const Vector4<Type> &aVector) const
{
	Vector4<Type> sum;
	sum.myX = myX - aVector.myX;
	sum.myY = myY - aVector.myY;
	sum.myZ = myZ - aVector.myZ;
	sum.myW = myW - aVector.myW;
	return sum;
}

template <class Type>
Vector4<Type> Vector4<Type>::operator*(const Type aTypeValue) const
{
	Vector4<Type> sum;
	sum.myX = myX * aTypeValue;
	sum.myY = myY * aTypeValue;
	sum.myZ = myZ * aTypeValue;
	sum.myW = myW * aTypeValue;
	return sum;
}

template <class Type>
Vector4<Type> Vector4<Type>::operator*(const Vector4<Type> &aVector) const
{
	Vector4<Type> sum;
	sum.myX = myX * aVector.myX;
	sum.myY = myY * aVector.myY;
	sum.myZ = myZ * aVector.myZ;
	sum.myW = myW * aVector.myW;
	return sum;
}

template <class Type>
Vector4<Type> Vector4<Type>::operator*(const Matrix44<Type> &aMatrix) const
{
	Vector4<Type> sum;
	sum.myX = (myX*aMatrix.myMatrix[0]) + (myY*aMatrix.myMatrix[4]) + (myZ*aMatrix.myMatrix[8]) + (myW*aMatrix.myMatrix[12]);
	sum.myY = (myX*aMatrix.myMatrix[1]) + (myY*aMatrix.myMatrix[5]) + (myZ*aMatrix.myMatrix[9]) + (myW*aMatrix.myMatrix[13]);
	sum.myZ = (myX*aMatrix.myMatrix[2]) + (myY*aMatrix.myMatrix[6]) + (myZ*aMatrix.myMatrix[10]) + (myW*aMatrix.myMatrix[14]);
	sum.myW = (myX*aMatrix.myMatrix[3]) + (myY*aMatrix.myMatrix[7]) + (myZ*aMatrix.myMatrix[11]) + (myW*aMatrix.myMatrix[15]);
	return sum;
}

template <class Type>
Vector4<Type> Vector4<Type>::operator/(const Vector4<Type> &aVector) const
{
	Vector4<Type> sum;
	sum.myX = myX / aVector.myX;
	sum.myY = myY / aVector.myY;
	sum.myZ = myZ / aVector.myZ;
	sum.myW = myW / aVector.myW;
	return sum;
}

template <class Type>
Vector4<Type> Vector4<Type>::operator/(const Type aTypeValue) const
{
	Vector4<Type> sum;
	sum.myX = myX / aTypeValue;
	sum.myY = myY / aTypeValue;
	sum.myZ = myZ / aTypeValue;
	sum.myW = myW / aTypeValue;
	return sum;
}


template <class Type>
Vector4<Type>& Vector4<Type>::operator+=(const Vector4<Type> &aVector)
{
	myX += aVector.myX;
	myY += aVector.myY;
	myZ += aVector.myZ;
	myW += aVector.myW;

	return (*this);
}

template <class Type>
Vector4<Type>& Vector4<Type>::operator-=(const Vector4<Type> &aVector)
{
	myX -= aVector.myX;
	myY -= aVector.myY;
	myZ -= aVector.myZ;
	myW -= aVector.myW;

	return (*this);
}

template <class Type>
Vector4<Type>& Vector4<Type>::operator*=(const Vector4<Type> &aVector)
{
	myX *= aVector.myX;
	myY *= aVector.myY;
	myZ *= aVector.myZ;
	myW *= aVector.myW;

	return (*this);
}

template <class Type>
Vector4<Type>& Vector4<Type>::operator/=(const Vector4<Type> &aVector)
{
	myX /= aVector.myX;
	myY /= aVector.myY;
	myZ /= aVector.myZ;
	myW /= aVector.myW;

	return (*this);
}

template <class Type>
bool Vector4<Type>::operator==(const Vector4<Type> &aVector) const
{
	if (myX == aVector.myX)
	{
		if (myY == aVector.myY)
		{
			if (myZ == aVector.myY)
			{
				if (myZ == aVector.myZ)
				{
					return true;
				}
			}
		}
	}
	return false;
}

template <class Type>
float Vector4<Type>::Length() const
{
	return( sqrt( (myX*myX) + (myY*myY) + (myZ*myZ) + (myW*myW) ) );
}

template <class Type>
Type Vector4<Type>::Dot(const Vector4<Type> &aVector) const
{
	return(myX * aVector.myX + myY * aVector.myY + myZ * aVector.myZ + myW * aVector.myW);
}


template <class Type>
Vector3<Type> Vector4<Type>::Vec3() const
{
	return Vector3f(myX,myY,myZ);
}

template <class Type>
void Vector4<Type>::Set(Type aX, Type anY, Type aZ, Type aW)
{
	myX = aX;
	myY = anY;
	myZ = aZ;
	myW = aW;
}

typedef Vector4<float> Vector4f;
typedef Vector4<int> Vector4i;

#endif