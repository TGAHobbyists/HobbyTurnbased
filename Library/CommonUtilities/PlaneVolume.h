#ifndef _PLANEVOLUME_H_
#define _PLANEVOLUME_H_

#include <vector>
#include "Plane.h"
#include "Vector.h"

template<typename Type>
class PlaneVolume
{
public:
	PlaneVolume (std::vector<SuperPlane<Type> > aPlaneList)
	{
		myPlanes = aPlaneList;
	}
	void AddPlane(SuperPlane<Type > aPlane)
	{
		myPlanes.push_back(aPlane);
	}

	void RemovePlane(SuperPlane<Type> aPlane)
	{
		for (unsigned int index = 0; index < myPlanes.size(); index++)
		{
			if (myPlanes[index] == aPlane)
			{
				myPlanes.erase(myPlanes.begin() + index);
				break;
			}
		}
	}

	const bool Inside(const Vector3<Type>& aPosition)
	{
		for (unsigned int index = 0; index < myPlanes.size(); index++)
		{			
			if(myPlanes[index].Inside(aPosition) == false)
			{
				return (false);
			}
		}
		return (true);
	}

private:
	std::vector< SuperPlane<Type> > myPlanes;
};
#endif //_PLANEVOLUME_H_