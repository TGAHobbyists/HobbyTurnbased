#ifndef _SELECTION_H_
#define _SELECTION_H_

#include "vector.h"
#include "sprite.h"

class Collision;

class Selection
{
public:
	Selection();
	Selection( Vector2f aMinPosition, Vector2f aMaxPosition );
	~Selection();

	void SetAnchor( const Vector2f& anAnchorPosition );
	void SetEnd( const Vector2f& anEndPosition );

	void Init();

	void Update( float aDeltaTime );
	void Render();

	void FinalizeSelection( Collision* aCollision );

private:
	Vector2f myMinPosition;
	Vector2f myMaxPosition;
	float myFlashTime;
	bool myHasSelection;
	Sprite mySprite;
};


#endif//_SELECTION_H_
