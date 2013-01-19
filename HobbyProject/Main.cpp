#include "stdafx.h"
#include <Windows.h>
#include "hge.h"
#include "App.h"
#include "Renderer.h"
#include "root.h"
#include "inputwrapper.h"
#include "mutexmanager.h"
#include "mutex.h"


HGE* HGE_Init( float aScreenWidth, float aScreenHeight )
{
	HGE* hgeInstance=NULL;

	hgeInstance=hgeCreate(HGE_VERSION);
	assert(hgeInstance != NULL);

	hgeInstance->System_SetState(HGE_LOGFILE, "HGE_Error.log");
	hgeInstance->System_SetState(HGE_TITLE, "HobbyProject");
	hgeInstance->System_SetState(HGE_WINDOWED, true);
	hgeInstance->System_SetState(HGE_SCREENWIDTH, (int)aScreenWidth);
	hgeInstance->System_SetState(HGE_SCREENHEIGHT, (int)aScreenHeight);
	hgeInstance->System_SetState(HGE_SCREENBPP, 32);
	hgeInstance->System_SetState(HGE_ZBUFFER, true);
	if( !hgeInstance->System_Initiate() )
	{
		hgeInstance->System_Shutdown();
		hgeInstance->Release();
		hgeInstance=NULL;
		assert( 0 && "hge initiate failed" );
	}

	return hgeInstance;

};

void HGE_Shutdown(HGE* aHGEInstance)
{
	aHGEInstance->System_Shutdown();
	aHGEInstance->Release();
}

int WINAPI WinMain(HINSTANCE , HINSTANCE , LPSTR , int )
{
	SetCurrentDirectory("..\\Bin");

	const Vector2f resolution( 800.f, 600.f );

	HGE* hgeEngine=HGE_Init( resolution.myX, resolution.myY );

	if(hgeEngine==NULL)
	{
		return(-1);
	}

	MSG windowsMessage;

	Renderer::Create( hgeEngine );
	Root::Create();

	Root::GetInstance()->myResolutionWidth = resolution.myX;
	Root::GetInstance()->myResolutionHeight = resolution.myY;

	Input::InputWrapper input;
	input.Initialize( hgeEngine->System_GetState( HGE_HWND ), Vector2f() );

	Root::GetInstance()->AttachInputWrapper( &input );

	MutexManager mutex;
	Root::GetInstance()->AttachMutexManager( &mutex );

	

	App application;

	application.Init();
	for(;;)
	{
		// check for messages
		if ( PeekMessage( &windowsMessage, NULL, 0, 0, PM_REMOVE ) ) 
		{
			// handle or dispatch messages
			if ( windowsMessage.message == WM_QUIT )
			{
				break;
			}
			TranslateMessage( &windowsMessage );
			DispatchMessage( &windowsMessage );
		} 
		else
		{
			application.update();
		}

	}
	input.Destroy();
	HGE_Shutdown(hgeEngine);

	// Clean up and shutdown
	return 0;
}
