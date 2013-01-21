#ifndef _COMMONMACROS_H_
#define _COMMONMACROS_H_
#include <sstream>
#include <string>
#include "math.h"



#ifndef IG_PI
#define IG_PI 3.141592f
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(aPointer) if( (aPointer) != NULL ) delete aPointer; aPointer = NULL
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(aPointer) if( (aPointer) != NULL ) delete [] aPointer; aPointer = NULL
#endif

#ifndef CLAMP
#define CLAMP(min, val, max) (val<min)?val=min:val=val;(val>max)?val=max:val=val;
#endif

#ifndef FOR_EACH_INDEX
#define FOR_EACH_INDEX(aCount) for(int index = 0; index < aCount; index++)
#endif

#ifndef RtD
#define RtD(radians) radians *(180/IG_PI)
#endif

#ifndef DtR
#define DtR(degrees) degrees * (IG_PI / 180)
#endif

namespace CommonUtilities
{
	namespace Macro
	{
		template <typename T>
		inline T Clamp(const T& aValue, const T& aMin, const T& aMax) 
		{
			return aValue < aMin ? aMin : (aValue > aMax ? aMax : aValue); 
		}
		template <typename T>
		inline T Clamp(T& aValue, T& aMin, T& aMax) 
		{
			return aValue < aMin ? aMin : (aValue > aMax ? aMax : aValue); 
		}

		template <typename T>
		inline T Lerp(const T& aLeftValue, const T& aRightValue, const T& aLerpValue) 
		{
			return (aLeftValue*(1-aLerpValue)) + (aRightValue * aLerpValue);
		}

		template <typename T>
		inline T Wrap(T aValue, const T& aMin, const T& aMax) 
		{
			const T diff = (aMax - aMin) + 1;
			while(aValue < aMin)
			{
				aValue += diff;
			}
			while (aValue > aMax)
			{
				aValue -= diff;
			}
			return aValue;
		}

		template <typename T>
		inline void Swap( T& aLeftSwap, T& aRightSwap )
		{
			T temp = aRightSwap;
			aLeftSwap = aRightSwap;
			aRightSwap = temp;
		}

		template <typename T>
		inline T Min(const T& aValue1, const T& aValue2)
		{
			return aValue1 < aValue2 ? aValue1 : aValue2;
		}

		template <typename T> 
		inline T Max(const T& aValue1, const T& aValue2)
		{
			return aValue1 > aValue2 ? aValue1 : aValue2;
		}

		template<class T>
		inline T ConvertFromString(const std::string& aString)
		{
			std::istringstream stream(aString);
			T value;
			stream >> value;
			return value;
		}

		inline float StringToFloat(const std::string& aString)
		{
			return ConvertFromString<float>(aString);
		}

		inline int StringToInt(const std::string& aString)
		{
			return ConvertFromString<int>(aString);
		}

		template<class T>
		inline std::string ConvertToString(const T& aValue)
		{
			std::ostringstream stream;
			stream << aValue;
			return stream.str();
		}

		inline std::string FloatToString(const float aValue)
		{
			return ConvertToString<float>(aValue);
		}

		inline std::string IntToString(const int aValue)
		{
			return ConvertToString<int>(aValue);
		}
	}
};

namespace CU = CommonUtilities;

#endif
