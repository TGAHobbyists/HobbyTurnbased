#include "FloatPlane.h"

FloatPlane::FloatPlane()
{

}

FloatPlane::FloatPlane( Vector3f aFirstPoint, Vector3f aSecondPoint, Vector3f aThirdPoint )
{
	myPoint = aFirstPoint;

	Vector3f myFirstVector;
	myFirstVector = aSecondPoint - myPoint;

	Vector3f mySecondVector;
	mySecondVector = aThirdPoint - myPoint;

	myNormal = myFirstVector.Cross(mySecondVector);

	myNormal = myNormal.Normalize();
}

FloatPlane::FloatPlane( Vector3f aPoint, Vector3f aNormal )
{
	myPoint = aPoint;
	myNormal = aNormal;
}

FloatPlane::~FloatPlane()
{

}

void FloatPlane::InitWith3Points( Vector3f aFirstPoint, Vector3f aSecondPoint, Vector3f aThirdPoint )
{
	myPoint = aFirstPoint;

	Vector3f myFirstVector;
	myFirstVector = aSecondPoint - myPoint;

	Vector3f mySecondVector;
	mySecondVector = aThirdPoint - myPoint;

	myNormal = myFirstVector.Cross(mySecondVector);
}

void FloatPlane::InitWithPointAndNormal( Vector3f aPoint, Vector3f aNormal )
{
	myPoint = aPoint;
	myNormal = aNormal;
}

bool FloatPlane::Inside( Vector3f aPosition )
{
	Vector3f tempVector = (aPosition - myPoint);
	if(myNormal.Dot(tempVector) > 0)
	{
		return (true);
	}
	return (false);
}

bool FloatPlane::operator==( const FloatPlane& aPlane ) const
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

void FloatPlane::NormalizePlane()
{
	myNormal = myNormal.Normalize();
}

