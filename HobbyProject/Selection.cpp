#include "stdafx.h"
#include "selection.h"

#include "dl_debug.h"
#include "collision.h"
#include "tile.h"
#include "renderer.h"

Selection::Selection()
: myFlashTime( 0.0f )
, myHasSelection( false )
{

}

Selection::Selection( Vector2f aMinPosition, Vector2f aMaxPosition)
: myMinPosition( aMinPosition )
, myMaxPosition( aMaxPosition )
, myFlashTime( 0.0f )
, myHasSelection( false )
{

}

Selection::~Selection()
{

}

void Selection::SetAnchor( const Vector2f& anAnchorPosition )
{
	myMinPosition = anAnchorPosition;
	myHasSelection = false;
}

void Selection::SetEnd( const Vector2f& anEndPosition )
{
	myMaxPosition = anEndPosition;
}
void Selection::Init()
{
	Vector2f tempSize( 16.f, 16.f );
	mySprite = Renderer::GetInstance()->CreateTexture( "Sprites/Terrain/Rock.bmp" );
	mySprite.SetSize( tempSize );
}

static const float flashTimer = 1.1f;
void Selection::Update( float aDeltaTime )
{
	if( myHasSelection )
	{
		myFlashTime += aDeltaTime;
		if( myFlashTime >= flashTimer * 2 )
		{
			myFlashTime = 0;
		}
	}
}
void Selection::Render()
{
	if( !myHasSelection )
	{
		Vector2f boxTopRight = Vector2f( myMaxPosition.myX, myMinPosition.myY );
		Vector2f boxBottomLeft = Vector2f( myMinPosition.myX, myMaxPosition.myY );
		Renderer::GetInstance()->LineRender( myMinPosition, boxTopRight );
		Renderer::GetInstance()->LineRender( myMinPosition, boxBottomLeft );
		Renderer::GetInstance()->LineRender( myMaxPosition, boxTopRight );
		Renderer::GetInstance()->LineRender( myMaxPosition, boxBottomLeft );
	}
	else
	{
		if( myFlashTime < flashTimer )
		{
			Renderer::GetInstance()->SpriteRender( &mySprite );
		}
	}
}

void Selection::FinalizeSelection( Collision* aCollision )
{
	myHasSelection = true;
	if( myMinPosition.myX > myMaxPosition.myX )
		CU::Macro::Swap( myMaxPosition.myX, myMinPosition.myX );
	if( myMinPosition.myY > myMaxPosition.myY )
		CU::Macro::Swap( myMaxPosition.myY, myMinPosition.myY );

	myMinPosition = aCollision->GetTileAt( myMinPosition ).myBox.GetMinPosition();
	myMaxPosition = aCollision->GetTileAt( myMaxPosition ).myBox.GetMaxPosition();

	mySprite.SetPosition( myMinPosition );
	Vector2f diff = myMaxPosition - myMinPosition;
	mySprite.SetSize( diff );
}
