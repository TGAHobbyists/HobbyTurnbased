#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "hge.h"
#include <string>
#include "cu_growingarray.h"
#include "vector.h"

#include "hgeFont.h"
class hgeSprite;
class Sprite;
class SpriteContainer;

enum TextAlignments
{
	ALIGN_LEFT = HGETEXT_LEFT,
	ALIGN_RIGHT = HGETEXT_RIGHT,
	ALIGN_CENTER = HGETEXT_CENTER,
	TEXT_ALIGNMENTS_SIZE
};

struct FontRenderMessage
{
	FontRenderMessage();
	FontRenderMessage( std::string aText, Vector2f aPosition, int anAlignment );
	std::string		myText;
	Vector2f		myPosition;
	int				myAlignment;
};

struct SpriteRenderMessage
{
	SpriteRenderMessage();
	SpriteRenderMessage( Vector2f aPosition, int aSpriteIndex, Vector2f aSize );
	Vector2f myPosition;
	Vector2f mySize;
	int mySpriteIndex;
};

struct LineRenderMessage
{
	LineRenderMessage();
	LineRenderMessage( Vector2f aPosition, Vector2f aEndPosition );
	Vector2f myPosition;
	Vector2f myEndPosition;
};

class Renderer
{
public:
	~Renderer();

	static bool			Create( HGE* aHGE );
	static void			Destroy();
	static Renderer*	GetInstance();

	void TextRender( std::string aText, Vector2f aPosition, int anAlignment );
	void SpriteRender( Sprite* aSprite );
	void LineRender( const Vector2f& aStartPosition, const Vector2f& anEndPosition );
	void Render();

	int CreateTexture( std::string aFilePath );
	Vector2f GetSpriteSize( int aSpriteIndex );

private:
	Renderer( HGE* aHGE );

	static Renderer* ourInstance;

	SpriteContainer* mySpriteContainer;

	HGE* myHGE;
	hgeFont* myFont;
	hgeSprite* mySprite;

	CU::GrowingArray< FontRenderMessage > myFontRenderMessages;
	CU::GrowingArray< SpriteRenderMessage > mySpriteRenderMessages;
	CU::GrowingArray< LineRenderMessage > myLineRenderMessages;

	

};


#endif//_RENDERER_H_