#include "stdafx.h"
#include "renderer.h"

#include "hgesprite.h"
#include "hgeFont.h"
#include "sprite.h"

#include "Camera.h"
#include "SpriteContainer.h"

FontRenderMessage::FontRenderMessage()
:myText("")
,myPosition( Vector2f(0.f,0.f) )
,myAlignment( -1 )
{}

FontRenderMessage::FontRenderMessage( std::string aText, Vector2f aPosition, int anAlignment )
:myText( aText )
,myPosition( aPosition )
,myAlignment( anAlignment )
{}

SpriteRenderMessage::SpriteRenderMessage()
:myPosition( Vector2f(0.f,0.f) )
,mySpriteIndex( -1 )
{}

SpriteRenderMessage::SpriteRenderMessage( Vector2f aPosition, int aSpriteIndex, Vector2f aSize )
:myPosition( aPosition )
,mySpriteIndex( aSpriteIndex )
,mySize( aSize )
{}

LineRenderMessage::LineRenderMessage()
{}

LineRenderMessage::LineRenderMessage( Vector2f aPosition, Vector2f aEndPosition )
: myPosition( aPosition )
, myEndPosition( aEndPosition )
{}

Renderer* Renderer::ourInstance = NULL;

Renderer::Renderer( HGE* aHGE )
:myHGE( aHGE )
{
	mySpriteContainer = new SpriteContainer();
	mySpriteContainer->Init( myHGE );

	HTEXTURE texture=myHGE->Texture_Load("ball.png");	
	mySprite=new hgeSprite(texture, 20.0f,20.0f,20.0f,20.0f);
	mySprite->SetBlendMode(0);

	myFont= new hgeFont("font1.fnt");
	myFont->SetColor( 0xFF000000 );
	myFontRenderMessages.Init( 10, 30 );
	mySpriteRenderMessages.Init( 100, 50 );
	myLineRenderMessages.Init( 40, 20 );
}

Renderer::~Renderer()
{
	SAFE_DELETE( mySpriteContainer );
}

bool Renderer::Create( HGE* aHGE )
{
	if( ourInstance == NULL )
	{
		ourInstance = new Renderer( aHGE  );
		return true;
	}
	return false;
}
void Renderer::Destroy()
{
	SAFE_DELETE( ourInstance );
}
Renderer* Renderer::GetInstance()
{
	return ourInstance;
}

void Renderer::TextRender( std::string aText, Vector2f aPosition, int anAlignment )
{
	myFontRenderMessages.Add( FontRenderMessage( aText, aPosition, anAlignment ) );
}

void Renderer::SpriteRender( Sprite* aSprite )
{
	Vector2f position;
	aSprite->GetPosition( position );
	mySpriteRenderMessages.Add( SpriteRenderMessage( position, aSprite->GetSpriteIndex(), aSprite->GetSize() ) );
}

void Renderer::LineRender( const Vector2f& aStartPosition, const Vector2f& anEndPosition )
{
	myLineRenderMessages.Add( LineRenderMessage( aStartPosition, anEndPosition ) );
}

void Renderer::Render()
{
	myHGE->Gfx_BeginScene();
	myHGE->Gfx_Clear( DWORD( 0xFFFFFFFF ) );

	const Vector2f vCameraOffset = Camera::getInstance()->getCameraOffset();

	int spriteIndex = -1;
	hgeSprite* sprite = NULL;
	for( int index = 0; index < mySpriteRenderMessages.Count(); ++index )
	{
		if( spriteIndex != mySpriteRenderMessages[ index ].mySpriteIndex )
			spriteIndex = mySpriteRenderMessages[ index ].mySpriteIndex;
		
		if( spriteIndex != -1 )
			sprite = mySpriteContainer->mySprites[ spriteIndex ].mySprite;
		else
			continue;
			
		float xScale = mySpriteRenderMessages[index].mySize.myX / sprite->GetWidth();
		float yScale = mySpriteRenderMessages[index].mySize.myY / sprite->GetHeight();

		if( xScale != 1.f )
			sprite = sprite;
		if( sprite != NULL )
			sprite->RenderEx( mySpriteRenderMessages[index].myPosition.myX - vCameraOffset.myX,
								mySpriteRenderMessages[index].myPosition.myY - vCameraOffset.myY,
								0.f,
								xScale,
								yScale
								);
	}

	for( int index = 0; index < myFontRenderMessages.Count(); ++index )
	{
		myFont->printf( myFontRenderMessages[index].myPosition.myX,
			myFontRenderMessages[index].myPosition.myY,
			myFontRenderMessages[index].myAlignment,
			myFontRenderMessages[index].myText.c_str()
			);
	}

	for( int index = 0; index < myLineRenderMessages.Count(); ++index )
	{
		myHGE->Gfx_RenderLine( myLineRenderMessages[index].myPosition.myX,
			myLineRenderMessages[index].myPosition.myY,
			myLineRenderMessages[index].myEndPosition.myX,
			myLineRenderMessages[index].myEndPosition.myY, 
			DWORD( 0xFFFF00FF ) );
	}


	myHGE->Gfx_EndScene();

	myFontRenderMessages.RemoveAll();
	mySpriteRenderMessages.RemoveAll();
	myLineRenderMessages.RemoveAll();
}

int Renderer::CreateTexture( std::string aFilePath )
{
	return mySpriteContainer->GetSprite( aFilePath );
}

Vector2f Renderer::GetSpriteSize( int aSpriteIndex )
{
	Vector2f size;

	if( aSpriteIndex >= 0 )
	{
		size.x = mySpriteContainer->mySprites[ aSpriteIndex ].mySprite->GetWidth();
		size.y = mySpriteContainer->mySprites[ aSpriteIndex ].mySprite->GetHeight();
	}

	return size;
}