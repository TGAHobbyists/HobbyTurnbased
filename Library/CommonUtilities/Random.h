#ifndef _MT_RAND_NAME_SPACE
#define _MT_RAND_NAME_SPACE
#include "MTRand.h"

class Random
{
public:
	Random();
	~Random();

	inline static Random* GetInstance();

	inline static void Seed(unsigned int aSeedValue);
	inline static int RandInt(const int aMaxValue);
	inline static float RandFloat();
	inline static float RandFloat(const float aMaxValue);

private:
	static Random* ourInstance;
	MTRand myRandom;
};

Random* Random::GetInstance()
{
	if (ourInstance == NULL)
	{
		ourInstance = new Random();
	}

	return ourInstance;
}

inline void Random::Seed(unsigned int aSeedValue)
{
	GetInstance()->myRandom.seed(aSeedValue);
}

inline int Random::RandInt(const int aMaxValue)
{
	return GetInstance()->myRandom.randInt(aMaxValue);
}

inline float Random::RandFloat()
{
	return GetInstance()->myRandom.rand();
}

inline float Random::RandFloat(const float aMaxValue)
{
	return GetInstance()->myRandom.rand() * aMaxValue;
}


#endif