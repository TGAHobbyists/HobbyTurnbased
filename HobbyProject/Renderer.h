#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "hge.h"
#include <string>
#include "cu_growingarray.h"
#include "vector.h"

#include "hgeFont.h"
class hgeSprite;

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


class Renderer
{
public:
	~Renderer();

	static bool			Create( HGE* aHGE );
	static void			Destroy();
	static Renderer*	GetInstance();

	void TextRender( std::string aText, Vector2f aPosition, int anAlignment );

	void Render();

private:
	Renderer( HGE* aHGE );

	static Renderer* ourInstance;

	HGE* myHGE;
	hgeFont* myFont;
	hgeSprite* mySprite;

	CU::GrowingArray< FontRenderMessage > myFontRenderMessages;

	

};


#endif//_RENDERER_H_