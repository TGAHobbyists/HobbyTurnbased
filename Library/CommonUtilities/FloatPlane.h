#ifndef _FLOAT_PLANE_H_
#define _FLOAT_PLANE_H_

#include "Vector.h"

class FloatPlane
{
public:
	FloatPlane();
	FloatPlane(Vector3f aFirstPoint, Vector3f aSecondPoint, Vector3f aThirdPoint);
	FloatPlane(Vector3f aPoint, Vector3f aNormal);
	~FloatPlane();

	void InitWith3Points(Vector3f aFirstPoint, Vector3f aSecondPoint, Vector3f aThirdPoint);
	void InitWithPointAndNormal(Vector3f aPoint, Vector3f aNormal);

	bool Inside(Vector3f aPosition);
	bool operator ==(const FloatPlane& aPlane) const;
	void NormalizePlane();
	Vector3f myPoint;
	Vector3f myNormal;

	private:
};
#endif