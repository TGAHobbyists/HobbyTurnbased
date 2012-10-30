#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H
#define DIRECTINPUT_VERSION 0x0800
#include <Windows.h>
#include "dinput.h"
#include "Vector.h"

namespace Input
{
	enum MouseButton
	{
		LeftMouseButton,
		RightMouseButton,
		MiddleMouseButton,
		NumberOfMouseButtons
	};

	class DirectInputWrapper
	{
	public:
		static const int	ourNumberOfCharsInKeyboardBuffer = 256;
		static const int	ourSizeOfCharBuffer = sizeof(char)*ourNumberOfCharsInKeyboardBuffer;
		static const DWORD	ourInputFlags = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;
	
	public:
		DirectInputWrapper();
		~DirectInputWrapper();

		void Initialize(HWND aWindowHandle);

		void Poll();
		void SwapBuffers();

		inline bool GetKeyPress(unsigned char aKey);
		inline bool GetKeyRelease(unsigned char aKey);
		inline bool GetMousePress(MouseButton aKey);
		inline bool GetMouseRelease(MouseButton aKey);

		inline int GetMouseX();
		inline int GetMouseY();
		inline int GetMouseZ();
		inline bool IsMouseWheelScrolledForward();
		inline bool IsMouseWheelScrolledBackward();

	private:
		void InitializeObject();
		void InitializeKeyboard(HWND aWindowHandle);
		void InitializeMouse(HWND aWindowHandle);

		inline bool IsKeyDown(unsigned char aKey, unsigned char* aKeyboardState);
		inline bool IsKeyUp(unsigned char aKey, unsigned char* aKeyboardState);
		inline bool IsMouseButtonDown(int aButton, DIMOUSESTATE2 &aMouseState);
		inline bool IsMouseButtonUp(int aButton, DIMOUSESTATE2 &aMouseState);
		
		inline void GetMouseState();
		inline void GetKeyboardState();

		DirectInputWrapper(const DirectInputWrapper &aInputWrapper);
		DirectInputWrapper& operator=(const DirectInputWrapper &aInputWrapper);
	
	private:
		DIMOUSESTATE2			myCurrentMouseState;
		DIMOUSESTATE2			myPreviousMouseState;
		unsigned char			*myCurrentKeyboardState;
		unsigned char			*myPreviousKeyboardState;
		LPDIRECTINPUT8			myDirectInput;
		LPDIRECTINPUTDEVICE8	myKeyboardDevice;
		LPDIRECTINPUTDEVICE8	myMouseDevice;
	};

	bool DirectInputWrapper::GetKeyRelease(unsigned char aKey)
	{
		if (IsKeyUp(aKey, myCurrentKeyboardState) == true)
		{
			return IsKeyDown(aKey, myPreviousKeyboardState);
		}
		return false;
	}

	bool DirectInputWrapper::GetKeyPress(unsigned char aKey)
	{
		if (IsKeyDown(aKey, myCurrentKeyboardState) == true)
		{
			return IsKeyUp(aKey, myPreviousKeyboardState);
		}
		return false;
	}

	bool DirectInputWrapper::IsKeyDown(unsigned char aKey, unsigned char* aKeyboardState)
	{
		return((aKeyboardState[aKey] & 0x80) != 0);
	}

	bool DirectInputWrapper::IsKeyUp(unsigned char aKey, unsigned char* aKeyboardState)
	{
		return(!IsKeyDown(aKey,aKeyboardState));
	}

	bool DirectInputWrapper::GetMouseRelease(MouseButton aKey)
	{
		if (IsMouseButtonUp(aKey, myCurrentMouseState) == true)
		{
			return IsMouseButtonDown(aKey, myPreviousMouseState);
		}
		return false;
	}

	bool DirectInputWrapper::GetMousePress(MouseButton aKey)
	{
		if (IsMouseButtonDown(aKey, myCurrentMouseState))
		{
			return IsMouseButtonUp(aKey, myPreviousMouseState);
		}
		return false;
	}

	bool DirectInputWrapper::IsMouseButtonDown(int aButton, DIMOUSESTATE2 &aMouseState)
	{
		return((aMouseState.rgbButtons[aButton] & 0x80) != 0);
	}

	bool DirectInputWrapper::IsMouseButtonUp(int aButton, DIMOUSESTATE2 &aMouseState)
	{
		return(!IsMouseButtonDown(aButton,aMouseState));
	}

	bool DirectInputWrapper::IsMouseWheelScrolledForward()
	{
		if( myCurrentMouseState.lZ > 0 )
		{
			return true;
		}
		return false;
	}

	bool DirectInputWrapper::IsMouseWheelScrolledBackward()
	{
		if( myCurrentMouseState.lZ < 0 )
		{
			return true;
		}
		return false;
	}

	int DirectInputWrapper::GetMouseX()
	{
		return(myCurrentMouseState.lX);
	}

	int DirectInputWrapper::GetMouseY()
	{
		return(myCurrentMouseState.lY);
	}

	int DirectInputWrapper::GetMouseZ()
	{
		return(myCurrentMouseState.lZ);
	}
}

#endif