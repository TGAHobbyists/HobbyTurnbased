#include "stdafx.h"
#include <Windows.h>
#include "hge.h"
#include "App.h"
#include "Renderer.h"
#include "root.h"

HGE* HGE_Init()
{
	HGE* hgeInstance=NULL;

	hgeInstance=hgeCreate(HGE_VERSION);

	hgeInstance->System_SetState(HGE_LOGFILE, "HGE_Error.log");
	hgeInstance->System_SetState(HGE_TITLE, "HobbyProject");
	hgeInstance->System_SetState(HGE_WINDOWED, true);
	hgeInstance->System_SetState(HGE_SCREENWIDTH, 800);
	hgeInstance->System_SetState(HGE_SCREENHEIGHT, 600);
	hgeInstance->System_SetState(HGE_SCREENBPP, 32);
	hgeInstance->System_SetState(HGE_ZBUFFER, true);
	if(!hgeInstance->System_Initiate())
	{
		hgeInstance->System_Shutdown();
		hgeInstance->Release();
		hgeInstance=NULL;
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

	HGE* hgeEngine=HGE_Init();

	if(hgeEngine==NULL)
	{
		return(-1);
	}

	MSG windowsMessage;

	Renderer::Create( hgeEngine );
	Root::Create();

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

	HGE_Shutdown(hgeEngine);

	// Clean up and shutdown
	return 0;
}
