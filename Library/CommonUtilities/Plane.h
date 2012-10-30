#ifndef _SUPER_PLANE_H_
#define _SUPER_PLANE_H_

#include "Vector.h"


template<class Type,class CountType = float>
class SuperPlane
{
public:

	SuperPlane();
	SuperPlane(Vector3<Type> aFirstPoint, Vector3<Type> aSecondPoint, Vector3<Type> aThirdPoint);
	SuperPlane(Vector3<Type> aPoint, Vector3<Type> aNormal);
	~SuperPlane();

	void InitWith3Points(Vector3<Type> aFirstPoint, Vector3<Type> aSecondPoint, Vector3<Type> aThirdPoint);
	void InitWithPointAndNormal(Vector3<Type> aPoint, Vector3<Type> aNormal);

	bool Inside(Vector3<Type> aPosition);
	bool operator ==(const SuperPlane<Type>& aPlane) const;

private:

	Vector3<Type> myPoint;
	Vector3<Type> myNormal;

};

template<class Type,class CountType>
SuperPlane<Type>::SuperPlane()
{
}

template<class Type,class CountType>
SuperPlane<Type>::SuperPlane(Vector3<Type> aFirstPoint, Vector3<Type> aSecondPoint, Vector3<Type> aThirdPoint)
{
	myPoint = aFirstPoint;

	Vector3<Type> myFirstVector;
	myFirstVector = aSecondPoint - myPoint;

	Vector3<Type> mySecondVector;
	mySecondVector = aThirdPoint - myPoint;

	myNormal = myFirstVector.Cross(mySecondVector);

}

template<class Type,class CountType>
SuperPlane<Type>::SuperPlane(Vector3<Type> aPoint, Vector3<Type> aNormal)
{
	myPoint = aPoint;
	myNormal = aNormal;
}

template<class Type,class CountType>
SuperPlane<Type>::~SuperPlane()
{
}

template<class Type,class CountType>
void SuperPlane<Type>::InitWith3Points(Vector3<Type> aFirstPoint, Vector3<Type> aSecondPoint, Vector3<Type> aThirdPoint)
{
	myPoint = aFirstPoint;

	Vector3<Type> myFirstVector;
	myFirstVector = aSecondPoint - myPoint;

	Vector3<Type> mySecondVector;
	mySecondVector = aThirdPoint - myPoint;

	myNormal = myFirstVector.Cross(mySecondVector);
}

template<class Type,class CountType>
void SuperPlane<Type>::InitWithPointAndNormal(Vector3<Type> aPoint, Vector3<Type> aNormal)
{
	myFirstPoint = aPoint;
	myNormal = aNormal;
}

template<class Type,class CountType>
bool SuperPlane<Type>::Inside(Vector3<Type> aPosition)
{
	Vector3<Type> tempVector = (aPosition - myPoint);
	if(myNormal.Dot(tempVector) > 0)
	{
		return (true);
	}
	return (false);
}

template<class Type,class CountType>
bool SuperPlane<Type>::operator ==(const Plane<Type>& aPlane) const
{
	if(myPoint == aPlane.myPoint)
	{
		if(myNormal == aPlane.myNormal)
		{
			return true;
		}
	}
	return false;
}


#endif