#include "InputWrapper.h"
#include "DL_Debug.h"

Input::InputWrapper::InputWrapper()
{
	myActiveInputBuffer = 0;
	myVisibleInputBuffer = 1;
	myThreadHandle = NULL;
	myIsActive = true;
}

Input::InputWrapper::~InputWrapper()
{
}

void Input::InputWrapper::Initialize(HWND aWindowHandle, const Vector2f& aDefaultMousePosition)
{
	myMousePosition = aDefaultMousePosition;
	myMouseMovement = Vector2f(0.0f,0.0f);
	myMouseWheel = 0;

	myInputWrapper.Initialize(aWindowHandle);

	myInputBuffers[myActiveInputBuffer].Init(1000,1000);
	myInputBuffers[myVisibleInputBuffer].Init(1000,1000);

	myThreadHandle = CreateThread(0, 0, InputThread, this, 0, 0);
}

void Input::InputWrapper::Destroy()
{
	TerminateThread(myThreadHandle, 0);
	WaitForSingleObject(myThreadHandle, INFINITE);
	CloseHandle(myThreadHandle);
}

void Input::InputWrapper::SwapBuffers()
{
	myMousePosition = Vector2f();
	int temp = myActiveInputBuffer;
	myActiveInputBuffer = myVisibleInputBuffer;
	myVisibleInputBuffer = temp;
	myInputBuffers[myActiveInputBuffer].RemoveAll();
}

void Input::InputWrapper::Pause()
{
	mySynchronizer.PauseThread();
}

void Input::InputWrapper::Resume()
{
	mySynchronizer.ResumeThread();
}

void Input::InputWrapper::Poll()
{
	if( myIsActive == true)
	{
	mySynchronizer.TryToWork();

 	myInputWrapper.Poll();
	AddKeyboardEvents();
	AddMouseEvents();
	myInputWrapper.SwapBuffers();

	mySynchronizer.EndWork();
	}
}

void Input::InputWrapper::AddKeyboardEvents()
{
	for (unsigned char keyIndex = 1; keyIndex <= numberOfKeysToCheck; keyIndex++)
	{
		if (myInputWrapper.GetKeyPress(keyIndex))
		{
			InputEvent event;
			event.myInputType		= Keyboard;
			event.myInputAction		= Press;
			event.myKey				= keyIndex;
			event.myMousePosition	= myMousePosition;
			myInputBuffers[myActiveInputBuffer].Add(event);
		}

		if (myInputWrapper.GetKeyRelease(keyIndex))
		{
			InputEvent event;
			event.myInputType		= Keyboard;
			event.myInputAction		= Release;
			event.myKey				= keyIndex;
			event.myMousePosition	= myMousePosition;
			myInputBuffers[myActiveInputBuffer].Add(event);
		}
	}
}

void Input::InputWrapper::AddMouseEvents()
{
	Vector3f mouseMovement(0,0,0);
	mouseMovement.myX = static_cast<float>(myInputWrapper.GetMouseX());
	mouseMovement.myY = static_cast<float>(myInputWrapper.GetMouseY());
	mouseMovement.myZ = static_cast<float>(myInputWrapper.GetMouseZ());
	myMousePosition += Vector2f(mouseMovement.x,mouseMovement.y);
	myMouseMovement += Vector2f(mouseMovement.x,mouseMovement.y);
	myMouseZ = mouseMovement.z;
	float mouseWheelMovement = static_cast<float>( myInputWrapper.GetMouseZ() );
	myMouseWheel += mouseWheelMovement;

	if( myInputWrapper.IsMouseWheelScrolledForward() == true )
	{
		InputEvent event;
		event.myInputType		= Mouse;
		event.myInputAction		= ScrollForward;
		event.myMouseWheel		= myMouseWheel;
		myInputBuffers[myActiveInputBuffer].Add( event );
		myMouseWheel = 0.0f;
	}
	if( myInputWrapper.IsMouseWheelScrolledBackward() == true )
	{
		InputEvent event;
		event.myInputType		= Mouse;
		event.myInputAction		= ScrollBackward;
		event.myMouseWheel		= myMouseWheel;
		myInputBuffers[myActiveInputBuffer].Add( event );
		myMouseWheel = 0.0f;
	}

	if (mouseMovement.myX != 0 || mouseMovement.myY != 0 || mouseMovement.myZ != 0)
	{
		InputEvent event;
		event.myInputType		= MousePosition;
		event.myMousePosition	= myMousePosition;
		myInputBuffers[myActiveInputBuffer].Add(event);
	}

	for (int mouseButtonIndex = 0; mouseButtonIndex < NumberOfMouseButtons; mouseButtonIndex++)
	{
		MouseButton button = static_cast<Input::MouseButton>(mouseButtonIndex);

		if (myInputWrapper.GetMousePress(button))
		{
			InputEvent event;
			event.myInputType		= Mouse;
			event.myInputAction		= Press;
			event.myMouseButton		= mouseButtonIndex;
			event.myMousePosition	= myMousePosition;
			myInputBuffers[myActiveInputBuffer].Add(event);
		}

		if (myInputWrapper.GetMouseRelease(button))
		{
			InputEvent event;
			event.myInputType		= Mouse;
			event.myInputAction		= Release;
			event.myMouseButton		= mouseButtonIndex;
			event.myMousePosition	= myMousePosition;
			myInputBuffers[myActiveInputBuffer].Add(event);
		}
	}
}

DWORD WINAPI Input::InputWrapper::InputThread(void *aInputHandler)
{
	InputWrapper* inputHandler = reinterpret_cast<Input::InputWrapper*>(aInputHandler);
	for (;;)
	{
		inputHandler->Poll();
	}
}
void Input::InputWrapper::SetActive(bool aState)
{
	myIsActive = aState;
}