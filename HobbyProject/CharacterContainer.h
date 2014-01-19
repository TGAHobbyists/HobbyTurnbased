#ifndef _CHARACTER_CONTAINER_H_
#define _CHARACTER_CONTAINER_H_

class CharacterContainer
{
public:
	CharacterContainer();
	~CharacterContainer();

	

private:
	CU::GrowingArray< Actor > myCharacters;
};

#endif//_CHARACTER_CONTAINER_H_
