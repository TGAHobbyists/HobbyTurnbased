#ifndef _DEBUG_LOGGER_H_
#define _DEBUG_LOGGER_H_

#include "FI_File.h"
#include <bitset>
#include <windows.h>

namespace DebugLogger
{
	enum Flags
	{
		Debug_Flag,
		Error_Flag,
		SevereError_Flag,
		CriticalError_Flag,
		NumberOfFlags
	};

	class Debug
	{
	public:
		static bool Create(std::string aFileName = "DebugLogger.txt", std::bitset<NumberOfFlags> someAssertFlags = 14);
		static bool Destroy();
		static Debug* GetInstance();

		void AssertMessage(const wchar_t* aFileName, const long aLine, const wchar_t* aFunctionName, const wchar_t* aMessage);
		
		void CriticalErrorMessage(const long aLine, const char* aFunctionName, const char* aFormat, ...);
		void SevereErrorMessage(const long aLine, const char* aFunctionName, const char* aFormat, ...);
		void ErrorMessage(const long aLine, const char* aFunctionName, const char* aFormat, ...);
		void DebugMessage(const long aLine, const char* aFunctionName, const char* aFormat, ...);
		void PrintMessage(const char* aMessage);


		void DisplayAndLogCallStackEntry(const char* anEntry);
		void PrintCallStack(HANDLE aThreadHandle = GetCurrentThread(), const CONTEXT *aExceptionContext = NULL);
		void PrintException(EXCEPTION_POINTERS* aException);
		void CreateMiniDump( EXCEPTION_POINTERS* anException );

	private:
		Debug();
		~Debug();

		void StartSession();
		bool EndSession(bool aForcedByAssert = false);

		void PrintAndOutputErrorData(const char* aWarningLevel, const long aLine, const char* aFunctionName, const char* aFormat, va_list someArguments);
		void TryToAbortAndWriteCallStack(Flags aAbortFlag);

		static std::string GetDate();
		static std::string GetTime();

		
		std::string ExceptionCodeToString(DWORD aExceptionCode);
		std::string ExceptionInformationToString(DWORD someExceptionInformation);

	private:
		static const int			ourSizeOfCharBuffers = 2048;
		static Debug*				ourInstance;
		FS::File					myLogFile;
		std::bitset<NumberOfFlags>	myAssertFlags;
	};
}

namespace DL = DebugLogger;

#ifdef  __cplusplus
extern "C" {
#endif

_CRTIMP void __cdecl _wassert(_In_z_ const wchar_t * _Message, _In_z_ const wchar_t *_File, _In_ unsigned _Line);

#ifdef  __cplusplus
}
#endif


#ifdef assert
#undef assert
#endif//assert



#define assert(_Expression) \
	__pragma(warning(disable:4127))\
	if (! (_Expression)) \
{ \
	DL_ASSERT(#_Expression);\
}



#define DL_ASSERT(string) { DL::Debug::GetInstance()->AssertMessage(_CRT_WIDE(__FILE__),__LINE__,_CRT_WIDE(__FUNCTION__),_CRT_WIDE(string)); }

#define DL_CRITICAL(condition,format, ...) { const bool _condition = condition; if (_condition == false) { DL::Debug::GetInstance()->CriticalErrorMessage(__LINE__,__FUNCTION__, format,__VA_ARGS__); }}
#define DL_SEVERE(condition,format, ...) { const bool _condition = condition; if (_condition == false) { DL::Debug::GetInstance()->SevereErrorMessage(__LINE__,__FUNCTION__, format,__VA_ARGS__); }}
#define DL_ERROR(condition,format, ...) { const bool _condition = condition; if (_condition == false) { DL::Debug::GetInstance()->ErrorMessage(__LINE__,__FUNCTION__, format,__VA_ARGS__); }}

#define DL_DEBUG(format, ...) DL::Debug::GetInstance()->DebugMessage(__LINE__,__FUNCTION__, format,__VA_ARGS__)
#define DL_PRINT(string) DL::Debug::GetInstance()->PrintMessage(string)

#endif