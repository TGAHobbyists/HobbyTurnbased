#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_
#include "CU_GrowingArray.h"
#include "DirectInputWrapper.h"
#include "PauseSynchronizer.h"
#include <Windows.h>
#include "Vector.h"


class HGE;
class hgeSprite;

namespace Input
{
	enum InputTypes
	{
		Keyboard,
		Mouse,
		MousePosition
	};

	enum InputAction
	{
		Press,
		Release,
		ScrollForward,
		ScrollBackward
	};

	struct InputEvent
	{
		Vector2f		myMousePosition;
		float			myMouseWheel;
		int				myMouseButton;
		InputTypes		myInputType;
		InputAction		myInputAction;
		unsigned char	myKey;
	};

	class InputWrapper
	{
	public:
		InputWrapper();
		~InputWrapper();

		void Initialize(HWND aWindowHandle, const Vector2f& aDefaultMousePosition = Vector2f(0,0));
		void Destroy();

		void Pause();
		void Resume();
		
		// Before calling any of these functions call Pause and when done call Resume
		void SwapBuffers();
		inline Vector2f GetMousePosition() const;
		inline Vector2f GetMouseMovement();
		inline float GetMouseZ();
		inline const CU::GrowingArray<InputEvent>& GetInputBuffer() const;

		void SetActive(bool aState);

	
	private:
		void Poll();
		void AddKeyboardEvents();
		void AddMouseEvents();
		static DWORD WINAPI InputThread(void *aInputHandler);
	
	private:
		static const int numberOfKeysToCheck = 237;

		DirectInputWrapper myInputWrapper;
		CU::GrowingArray<InputEvent>	myInputBuffers[2];
		
		PauseSynchronizer mySynchronizer;
		Vector2f myMousePosition;
		Vector2f myMouseMovement;
		float myMouseWheel;
		float myMouseZ;
		HANDLE myThreadHandle;
		
		int myActiveInputBuffer;
		int myVisibleInputBuffer;
		bool myIsActive;
	};

	const CU::GrowingArray<InputEvent>& InputWrapper::GetInputBuffer() const
	{
		return myInputBuffers[myVisibleInputBuffer];
	}

	Vector2f InputWrapper::GetMousePosition() const
	{
		return myMousePosition;
	}

	Vector2f InputWrapper::GetMouseMovement()
	{
		//myMouseMovement = Vector2f(0.0f,0.0f);
		return myMouseMovement;
	}
	float InputWrapper::GetMouseZ()
	{
		float aMouseZ = myMouseZ;
		myMouseZ = 0;
		return aMouseZ;
	}
}

#endif