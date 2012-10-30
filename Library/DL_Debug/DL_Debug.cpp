#include "DL_Debug.h"
#include "StackWalker.h"
#include "Time.h"
#include <iostream>
#include <Dbghelp.h>
#include "assert.h"

DL::Debug* DL::Debug::ourInstance = NULL;

DL::Debug::Debug()
{

}

DL::Debug::~Debug()
{

}

void ExceptionHandler()
{
	DL_PRINT("Default Exception Handler Triggered!");
	DL::Debug::GetInstance()->PrintCallStack();
	abort();
}

LONG WINAPI ExceptionFilter(EXCEPTION_POINTERS* aException)
{
	DL::Debug::GetInstance()->PrintException(aException);
	DL::Debug::GetInstance()->PrintCallStack(GetCurrentThread(), aException->ContextRecord);
	DL::Debug::GetInstance()->CreateMiniDump( aException );


	return EXCEPTION_EXECUTE_HANDLER;
}

bool DL::Debug::Create(std::string aFileName, std::bitset<NumberOfFlags> someAssertFlags)
{
	//EXCEPTION_ACCESS_VIOLATION;
	ourInstance	= new Debug();
	ourInstance->myAssertFlags = someAssertFlags;

	std::bitset<8> logFileParameters;
	logFileParameters.reset();
	logFileParameters.set(FS::File::WRITE);

	if (ourInstance != NULL)
	{
		if (ourInstance->myLogFile.Open(aFileName,logFileParameters))
		{
			ourInstance->StartSession();
		}
		else
		{
			delete ourInstance;
			ourInstance = NULL;
			return(false);
		}
	}

	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)&ExceptionFilter);
	set_terminate(ExceptionHandler);
	set_unexpected(ExceptionHandler);

	return(true);
}

bool DL::Debug::Destroy()
{
	if (ourInstance != NULL)
	{
		if (ourInstance->EndSession() == false)
		{
			return(false);
		}
	}

	delete ourInstance;
	ourInstance = NULL;

	if (ourInstance != NULL)
	{
		return(false);
	}

	return(true);
}

DL::Debug* DL::Debug::GetInstance()
{
	return(ourInstance);
}

void DL::Debug::AssertMessage(const wchar_t* aFileName, long aLine, const wchar_t* aFunctionName, const wchar_t* aMessage)
{
	char outputBuffer[ourSizeOfCharBuffers];
	sprintf_s(outputBuffer,"%s ASSERT File: %ls Function: %ls() Line: %d \"%ls\"", GetTime().c_str(), aFileName, aFunctionName, aLine, aMessage);
	std::cout<<outputBuffer<<std::endl;
	myLogFile.WriteString(std::string(outputBuffer));
	myLogFile.FlushToDisk();
	EndSession();
	PrintCallStack();
	_wassert(aMessage, aFileName, aLine);
}

void DL::Debug::SevereErrorMessage(const long aLine, const char* aFunctionName, const char* aFormat, ...)
{
	va_list argumentList;
	va_start(argumentList, aFormat);
	PrintAndOutputErrorData("SEVERE ERROR", aLine, aFunctionName, aFormat, argumentList);
	va_end(argumentList);
	TryToAbortAndWriteCallStack(SevereError_Flag);
}


void DL::Debug::CriticalErrorMessage(const long aLine, const char* aFunctionName, const char* aFormat, ...)
{
	va_list argumentList;
	va_start(argumentList, aFormat);
	PrintAndOutputErrorData("CRITICAL ERROR", aLine, aFunctionName, aFormat, argumentList);
	va_end(argumentList);
	TryToAbortAndWriteCallStack(CriticalError_Flag);
}


void DL::Debug::ErrorMessage(const long aLine, const char* aFunctionName, const char* aFormat, ...)
{
	va_list argumentList;
	va_start(argumentList, aFormat);
	PrintAndOutputErrorData("ERROR", aLine, aFunctionName, aFormat, argumentList);
	va_end(argumentList);
	TryToAbortAndWriteCallStack(Error_Flag);
}

void DL::Debug::TryToAbortAndWriteCallStack(Flags aAbortFlag)
{
	if (myAssertFlags.test(aAbortFlag))
	{
		PrintCallStack();
		EndSession(true);
		abort();
	}
}

void DL::Debug::DebugMessage(const long aLine, const char* aFunctionName, const char* aFormat, ...)
{
	va_list argumentList;
	va_start(argumentList, aFormat);
	PrintAndOutputErrorData("DEBUG", aLine, aFunctionName, aFormat, argumentList);
	va_end(argumentList);
	TryToAbortAndWriteCallStack(Debug_Flag);
}

void DL::Debug::PrintMessage(const char* aMessage)
{
	char outputBuffer[ourSizeOfCharBuffers];
	sprintf_s(outputBuffer,"%s MESSAGE %s", GetTime().c_str(), aMessage);
	myLogFile.WriteString(std::string(outputBuffer));
	myLogFile.FlushToDisk();
	std::cout<<outputBuffer<<std::endl;
}

void DL::Debug::DisplayAndLogCallStackEntry(const char* anEntry)
{
	std::string outputString(anEntry);
	outputString.resize(outputString.size()-1);
	std::cout<<outputString<<std::endl;
	myLogFile.WriteString(outputString);
}

void DL::Debug::PrintCallStack(HANDLE aThreadHandle, const CONTEXT *aExceptionContext)
{
	const std::string dumpCallStackMessage("Dumping call stack...");
	std::cout<<std::endl<<dumpCallStackMessage<<std::endl<<std::endl;
	myLogFile.WriteString("");
	myLogFile.WriteString(dumpCallStackMessage);
	myLogFile.WriteString("");
	BaseStackWalker ws;
	ws.ShowCallstack(aThreadHandle, aExceptionContext);
	myLogFile.FlushToDisk();
}

void DL::Debug::PrintAndOutputErrorData(const char* aWarningLevel, const long aLine, const char* aFunctionName, const char* aFormat, va_list someArguments)
{
	char outputBuffer[ourSizeOfCharBuffers];
	sprintf_s(outputBuffer,"%s %s Function: %s() Line: %d", GetTime().c_str(), aWarningLevel, aFunctionName, aLine);

	char vaargsOutput[ourSizeOfCharBuffers];
	vsprintf_s(vaargsOutput, aFormat, someArguments);

	std::string output(outputBuffer);
	output += " \"";
	output += vaargsOutput;
	output += "\"";

	std::cout<<output<<std::endl;
	myLogFile.WriteString(output);
	myLogFile.FlushToDisk();
}

void DL::Debug::StartSession()
{
	std::string startLogMessage = "Starting session ";
	startLogMessage += GetDate();
	startLogMessage += " ";
	startLogMessage += GetTime();
	std::cout<<startLogMessage<<std::endl;
	myLogFile.WriteString(startLogMessage);

	char* date = __DATE__;
	char* time = __TIME__;
	std::string compilationMessage = "Binaries compiled ";
	compilationMessage += date;
	compilationMessage += " ";
	compilationMessage += time;
	std::cout<<compilationMessage<<std::endl;
	myLogFile.WriteString(compilationMessage);
}

bool DL::Debug::EndSession(bool aForcedByAssert)
{
	std::string endSessionMessage = "Closed session ";
	endSessionMessage += GetDate();
	endSessionMessage += " ";
	endSessionMessage += GetTime();

	if (aForcedByAssert)
	{
		std::cout<<std::endl;
		myLogFile.WriteString("");
	}

	std::cout<<endSessionMessage<<std::endl<<std::endl;
	myLogFile.WriteString(endSessionMessage);
	myLogFile.WriteString("");

	return myLogFile.Close();
}

std::string DL::Debug::GetDate()
{
	SYSTEMTIME systemTime;  
	GetSystemTime(&systemTime);

	std::stringstream stringStream;

	stringStream << systemTime.wYear << "-";
	stringStream << systemTime.wMonth << "-";
	stringStream << systemTime.wDay;

	return(stringStream.str());
}

std::string DL::Debug::GetTime()
{
	SYSTEMTIME localTime;  
	GetLocalTime(&localTime);

	int hour	= localTime.wHour;
	int minute	= localTime.wMinute;
	int second	= localTime.wSecond;

	std::stringstream stringStream;

	if (hour < 10)
	{
		stringStream<<"0";
	}
	stringStream << hour << ":";

	if (minute < 10)
	{
		stringStream<<"0";
	}
	stringStream << minute << ":";

	if (second < 10)
	{
		stringStream<<"0";
	}
	stringStream << second;

	return(stringStream.str());
}

std::string DL::Debug::ExceptionCodeToString(DWORD aExceptionCode)
{
	switch(aExceptionCode)
	{
	case EXCEPTION_ACCESS_VIOLATION:
		return "EXCEPTION_ACCESS_VIOLATION";
		break;
	case EXCEPTION_DATATYPE_MISALIGNMENT:
		return "EXCEPTION_DATATYPE_MISALIGNMENT";
		break;
	case EXCEPTION_BREAKPOINT:
		return "EXCEPTION_BREAKPOINT";
		break;
	case EXCEPTION_SINGLE_STEP:
		return "EXCEPTION_SINGLE_STEP";
		break;
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
		break;
	case EXCEPTION_FLT_DENORMAL_OPERAND:
		return "EXCEPTION_FLT_DENORMAL_OPERAND";
		break;
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		return "EXCEPTION_FLT_DIVIDE_BY_ZERO";
		break;
	case EXCEPTION_FLT_INEXACT_RESULT:
		return "EXCEPTION_FLT_INEXACT_RESULT";
		break;
	case EXCEPTION_FLT_INVALID_OPERATION:
		return "EXCEPTION_FLT_INVALID_OPERATION";
		break;
	case EXCEPTION_FLT_OVERFLOW:
		return "EXCEPTION_FLT_OVERFLOW";
		break;
	case EXCEPTION_FLT_STACK_CHECK:
		return "EXCEPTION_FLT_STACK_CHECK";
		break;
	case EXCEPTION_FLT_UNDERFLOW:
		return "EXCEPTION_FLT_UNDERFLOW";
		break;
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		return "EXCEPTION_INT_DIVIDE_BY_ZERO";
		break;
	case EXCEPTION_INT_OVERFLOW:
		return "EXCEPTION_INT_OVERFLOW";
		break;
	case EXCEPTION_PRIV_INSTRUCTION:
		return "EXCEPTION_PRIV_INSTRUCTION";
		break;
	case EXCEPTION_IN_PAGE_ERROR:
		return "EXCEPTION_IN_PAGE_ERROR";
		break;
	case EXCEPTION_ILLEGAL_INSTRUCTION:
		return "EXCEPTION_ILLEGAL_INSTRUCTION";
		break;
	case EXCEPTION_NONCONTINUABLE_EXCEPTION:
		return "EXCEPTION_NONCONTINUABLE_EXCEPTION";
		break;
	case EXCEPTION_STACK_OVERFLOW:
		return "EXCEPTION_STACK_OVERFLOW";
		break;
	case EXCEPTION_INVALID_DISPOSITION:
		return "EXCEPTION_INVALID_DISPOSITION";
		break;
	case EXCEPTION_GUARD_PAGE:
		return "EXCEPTION_GUARD_PAGE";
		break;
	case EXCEPTION_INVALID_HANDLE:
		return "EXCEPTION_INVALID_HANDLE";
		break;
	default:
		return "UNKNWON EXCEPTION";
		break;
	}
}

std::string DL::Debug::ExceptionInformationToString(DWORD someExceptionInformation)
{
	switch(someExceptionInformation)
	{
	case 0:
		return "Read";
		break;
	case 1:
		return "Write";
		break;
	default:
		return "UNKNWON EXCEPTION INFORMATION";
		break;
	}
}

void DL::Debug::PrintException(EXCEPTION_POINTERS* aException)
{
	char outputBuffer[ourSizeOfCharBuffers];

	switch (aException->ExceptionRecord->ExceptionCode)
	{
	case EXCEPTION_ACCESS_VIOLATION:
		sprintf_s(outputBuffer,"\nUNHANDLED EXCEPTION (%p)\nCode: %s\nLocation: %p\nOperation: %s\nAddress: %p", aException->ExceptionRecord->ExceptionCode, ExceptionCodeToString(aException->ExceptionRecord->ExceptionCode).c_str(), aException->ExceptionRecord->ExceptionAddress, ExceptionInformationToString(aException->ExceptionRecord->ExceptionInformation[0]).c_str(), aException->ExceptionRecord->ExceptionInformation[1]);
		break;
	default:
		sprintf_s(outputBuffer,"\nUNHANDLED EXCEPTION (%p)\nCode: %s\nLocation: %p", aException->ExceptionRecord->ExceptionCode, ExceptionCodeToString(aException->ExceptionRecord->ExceptionCode).c_str(), aException->ExceptionRecord->ExceptionAddress);
		break;
	}
	std::cout<<outputBuffer<<std::endl;
	myLogFile.WriteString(std::string(outputBuffer));
}
void DL::Debug::CreateMiniDump( EXCEPTION_POINTERS* pep )
{
	// Open the file 
	typedef BOOL (*PDUMPFN)( 
		HANDLE hProcess, 
		DWORD ProcessId, 
		HANDLE hFile, 
		MINIDUMP_TYPE DumpType, 
		PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, 
		PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, 
		PMINIDUMP_CALLBACK_INFORMATION CallbackParam
		);


	HANDLE hFile = CreateFile( "MiniDump.dmp", GENERIC_READ | GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 

	HMODULE h = ::LoadLibrary("DbgHelp.dll");
	PDUMPFN pFn = (PDUMPFN)GetProcAddress(h, "MiniDumpWriteDump");

	if( ( hFile != NULL ) && ( hFile != INVALID_HANDLE_VALUE ) ) 
	{
		// Create the minidump 

		MINIDUMP_EXCEPTION_INFORMATION mdei; 

		mdei.ThreadId           = GetCurrentThreadId(); 
		mdei.ExceptionPointers  = pep; 
		mdei.ClientPointers     = TRUE; 

		MINIDUMP_TYPE mdt       = MiniDumpNormal; 

		BOOL rv = (*pFn)( GetCurrentProcess(), GetCurrentProcessId(), 
			hFile, mdt, (pep != 0) ? &mdei : 0, 0, 0 ); 


		rv;
		// Close the file 

		CloseHandle( hFile ); 

	}

}
