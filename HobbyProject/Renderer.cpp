#include "stdafx.h"
#include "renderer.h"

#include "hgesprite.h"
#include "hgeFont.h"
#include "sprite.h"

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
,mySprite( NULL )
{}
SpriteRenderMessage::SpriteRenderMessage( Vector2f aPosition, hgeSprite* aSprite )
:myPosition( aPosition )
,mySprite( aSprite )
{}

Renderer* Renderer::ourInstance = NULL;

Renderer::Renderer( HGE* aHGE )
:myHGE( aHGE )
{
	HTEXTURE texture=myHGE->Texture_Load("ball.png");	
	mySprite=new hgeSprite(texture, 20.0f,20.0f,20.0f,20.0f);
	mySprite->SetBlendMode(0);

	myFont= new hgeFont("font1.fnt");
	myFontRenderMessages.Init( 10, 30 );
	mySpriteRenderMessages.Init( 100, 50 );
}

Renderer::~Renderer()
{

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
	mySpriteRenderMessages.Add( SpriteRenderMessage( position, aSprite->GetRawSprite() ) );
}

void Renderer::Render()
{
	myHGE->Gfx_BeginScene();	
	myHGE->Gfx_Clear(0);

	for( int index = 0; index < mySpriteRenderMessages.Count(); ++index )
	{
		mySpriteRenderMessages[index].mySprite->RenderEx( 
			mySpriteRenderMessages[index].myPosition.myX,
			mySpriteRenderMessages[index].myPosition.myY,
			0.f
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




	myHGE->Gfx_EndScene();

	myFontRenderMessages.RemoveAll();
	mySpriteRenderMessages.RemoveAll();
}
HTEXTURE Renderer::CreateTexture( std::string aFilePath )
{
	HTEXTURE texture = myHGE->Texture_Load( aFilePath.c_str() );
	return texture;
}

