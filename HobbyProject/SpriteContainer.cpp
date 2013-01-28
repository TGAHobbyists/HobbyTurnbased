#include "stdafx.h"
#include "SpriteContainer.h"

#include "HGE.h"
#include "hgeSprite.h"

SpriteContainer::SpriteContainer()
{}

SpriteContainer::~SpriteContainer()
{
	for( int i = mySprites.Count() - 1; i >= 0; --i )
	{
		SAFE_DELETE( mySprites[ i ].mySprite );
	}
}

void SpriteContainer::Init( HGE* aHGE )
{
	myHge = aHGE;

	mySprites.Init( 5, 10 );
	HTEXTURE tex; 
	hgeSprite* sprite;
	Sprites sprites;

	tex = myHge->Texture_Load( "Sprites//Terrain//Grass.bmp" );
	sprite = new hgeSprite( tex,  0.0f,  0.0f, ( float )myHge->Texture_GetWidth( tex ), ( float )myHge->Texture_GetHeight( tex ) );
	sprites.myName = "Sprites//Terrain//Grass.bmp";
	sprites.mySprite = sprite;
	mySprites.Add( sprites );

	tex = myHge->Texture_Load( "Sprites//Terrain//Dirt.bmp" );
	sprite = new hgeSprite( tex,  0.0f,  0.0f, ( float )myHge->Texture_GetWidth( tex ), ( float )myHge->Texture_GetHeight( tex ) );
	sprites.myName = "Sprites//Terrain//Dirt.bmp";
	sprites.mySprite = sprite;
	mySprites.Add( sprites );

	tex = myHge->Texture_Load( "Sprites//Terrain//Rock.bmp" );
	sprite = new hgeSprite( tex,  0.0f,  0.0f, ( float )myHge->Texture_GetWidth( tex ), ( float )myHge->Texture_GetHeight( tex ) );
	sprites.myName = "Sprites//Terrain//Rock.bmp";
	sprites.mySprite = sprite;
	mySprites.Add( sprites );

	tex = myHge->Texture_Load( "Sprites//Unit//Unit.png" );
	sprite = new hgeSprite( tex,  0.0f,  0.0f, ( float )myHge->Texture_GetWidth( tex ), ( float )myHge->Texture_GetHeight( tex ) );
	sprites.myName = "Sprites//Unit//Unit.png";
	sprites.mySprite = sprite;
	mySprites.Add( sprites );

	tex = myHge->Texture_Load( "WhiteBackground.BMP" );
	sprite = new hgeSprite( tex,  0.0f,  0.0f, ( float )myHge->Texture_GetWidth( tex ), ( float )myHge->Texture_GetHeight( tex ) );
	sprites.myName = "WhiteBackground.BMP";
	sprites.mySprite = sprite;
	mySprites.Add( sprites );

	tex = myHge->Texture_Load( "Sprites//Fab cursor.png" );
	sprite = new hgeSprite( tex, 0.0f, 0.0f, ( float )myHge->Texture_GetWidth( tex ), ( float )myHge->Texture_GetHeight( tex ) );
	sprites.myName = "Sprites//Fab cursor.png";
	sprites.mySprite = sprite;
	mySprites.Add( sprites );

	mySprites.Optimize();
}

const int SpriteContainer::GetSprite( const std::string& aSprite )
{
	const int size = mySprites.Count();
	for( int i = 0; i < size; ++i )
	{
		if( mySprites[ i ].myName == aSprite )
			return i;
	}
	
	return -1;
}