#include "InputWrapper.h"

Input::DirectInputWrapper::DirectInputWrapper() :
	myCurrentKeyboardState(NULL),
	myPreviousKeyboardState(NULL)
{
	
}

Input::DirectInputWrapper::DirectInputWrapper(const DirectInputWrapper &aInputWrapper)
{
	aInputWrapper;
}

Input::DirectInputWrapper& Input::DirectInputWrapper::operator=(const DirectInputWrapper &aInputWrapper)
{
	aInputWrapper;
	return (*this);
}

void Input::DirectInputWrapper::Initialize(HWND aWindowHandle)
{
	InitializeObject();
	InitializeKeyboard(aWindowHandle);
	InitializeMouse(aWindowHandle);
}

void Input::DirectInputWrapper::InitializeObject()
{
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(&myDirectInput), NULL);
}

void Input::DirectInputWrapper::InitializeKeyboard(HWND aWindowHandle)
{
	myCurrentKeyboardState = new unsigned char[ourNumberOfCharsInKeyboardBuffer];
	ZeroMemory(&myCurrentKeyboardState[0], ourSizeOfCharBuffer);
	myPreviousKeyboardState = new unsigned char[ourNumberOfCharsInKeyboardBuffer];
	ZeroMemory(&myPreviousKeyboardState[0], ourSizeOfCharBuffer);
	myDirectInput->CreateDevice(GUID_SysKeyboard, &myKeyboardDevice, NULL);
	myKeyboardDevice->SetCooperativeLevel(aWindowHandle, ourInputFlags);
	myKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	myKeyboardDevice->Acquire();
}

void Input::DirectInputWrapper::InitializeMouse(HWND aWindowHandle)
{
	ZeroMemory(&myCurrentMouseState, sizeof(DIMOUSESTATE2));
	ZeroMemory(&myPreviousMouseState, sizeof(DIMOUSESTATE2));
	myDirectInput->CreateDevice(GUID_SysMouse, &myMouseDevice, NULL);
	myMouseDevice->SetCooperativeLevel(aWindowHandle, ourInputFlags);
	myMouseDevice->SetDataFormat(&c_dfDIMouse2);
	myMouseDevice->Acquire();
}

void Input::DirectInputWrapper::Poll()
{
	myKeyboardDevice->Poll();
	GetKeyboardState();
	GetMouseState();
}

void Input::DirectInputWrapper::GetKeyboardState()
{
	if (FAILED(myKeyboardDevice->GetDeviceState(ourSizeOfCharBuffer, reinterpret_cast<void*>(myCurrentKeyboardState))))
	{
		myKeyboardDevice->Acquire();
	}
}

void Input::DirectInputWrapper::GetMouseState()
{
	if (FAILED(myMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), reinterpret_cast<void**>(&myCurrentMouseState))))
	{
		myMouseDevice->Acquire();
	}
}

void Input::DirectInputWrapper::SwapBuffers()
{
	unsigned char* previousKeyboardState = myPreviousKeyboardState;
	myPreviousKeyboardState	= myCurrentKeyboardState;
	myCurrentKeyboardState	= previousKeyboardState;
	myPreviousMouseState	= myCurrentMouseState;
}

Input::DirectInputWrapper::~DirectInputWrapper()
{

}