#include "stdafx.h"
#include "renderer.h"

#include "hgesprite.h"
#include "hgeFont.h"
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

Renderer* Renderer::ourInstance = NULL;

Renderer::Renderer( HGE* aHGE )
:myHGE( aHGE )
{
	HTEXTURE texture=myHGE->Texture_Load("ball.png");	
	mySprite=new hgeSprite(texture, 20.0f,20.0f,20.0f,20.0f);
	mySprite->SetBlendMode(0);

	myFont= new hgeFont("font1.fnt");
	myFontRenderMessages.Init( 10, 30 );
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

void Renderer::Render()
{
	myHGE->Gfx_BeginScene();	
	myHGE->Gfx_Clear(0);

	for( int index = 0; index < myFontRenderMessages.Count(); ++index )
	{
		myFont->printf( myFontRenderMessages[index].myPosition.myX,
			myFontRenderMessages[index].myPosition.myY,
			myFontRenderMessages[index].myAlignment,
			myFontRenderMessages[index].myText.c_str()
			);

	}

	myFont->printf( 400, 300, HGETEXT_LEFT, "Hello pebkac" );

	myHGE->Gfx_EndScene();

	myFontRenderMessages.RemoveAll();
}


