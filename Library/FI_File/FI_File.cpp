#include "FI_File.h"

const char FS::File::mySpaceCharacter = ' ';
const char FS::File::myEndLineCharacter = GetNewLineCharacterForSystem();

FS::File::File(void)
{

}

FS::File::~File(void)
{
	Close();
}

bool FS::File::Open(std::string aFileName, std::bitset<8> aSetOfFlags)
{
	myLastActionWasReading = true;
	myLastActionWasWriting = true;
	myFlags = aSetOfFlags;
	
	myFileStream.open(aFileName.c_str(), SetFlagsInOpeningParameters(aSetOfFlags));
	return myFileStream.is_open();
}

std::fstream::open_mode FS::File::SetFlagsInOpeningParameters(std::bitset<8> aSetOfFlags)
{
	std::fstream::open_mode parameters = 0;

	if (aSetOfFlags.test(READ) == true)
	{
		parameters |= std::fstream::in;
	}
	if (aSetOfFlags.test(WRITE) == true)
	{
		parameters |= std::fstream::out;
	}
	if (aSetOfFlags.test(APPEND) == true)
	{
		parameters |= std::fstream::app;
	}
	if (aSetOfFlags.test(BINARY) == true)
	{
		parameters |= std::fstream::binary;
	}

	return parameters;
}

bool FS::File::Close()
{
	if (myFileStream.is_open())
	{
		myFileStream.close();
		myFileStream.clear();
		return myFileStream.good();
	}
	return false;
}

bool FS::File::GoToNewLine()
{
	SynchronizeGetPointer();

	if (CheckIfReadIsPossible())
	{
		if (myFlags.test(BINARY) == false)
		{
			char readChar = mySpaceCharacter;

			do
			{
				myFileStream.get(readChar);
			} 
			while (readChar != myEndLineCharacter);

			return myFileStream.good();
		}
	}
	return false;
}


bool FS::File::ReadInt(int& aInteger)
{
	SynchronizeGetPointer();

	if (CheckIfReadIsPossible())
	{
		if (IsBinary())
		{
			ReadData(&aInteger, sizeof(int));
		}
		else
		{
			myFileStream>>aInteger;
		}
		return myFileStream.good();
	}
	return false;
}

bool FS::File::ReadFloat(float& aFloat)
{
	SynchronizeGetPointer();

	if (CheckIfReadIsPossible())
	{
		if (IsBinary())
		{
			ReadData(&aFloat, sizeof(float));
		}
		else
		{
			myFileStream.precision(myNumberOfFloatDecimalDigets);
			myFileStream>>aFloat;
		}
		return myFileStream.good();
	}
	return false;
}

bool FS::File::ReadDouble(double& aDouble)
{
	SynchronizeGetPointer();

	if (CheckIfReadIsPossible())
	{
		if (IsBinary())
		{
			ReadData(&aDouble, sizeof(double));
		}
		else
		{
			myFileStream.precision(myNumberOfDoubleDecimalDigets);
			myFileStream>>aDouble;
		}
		return myFileStream.good();
	}
	return false;
}

bool FS::File::ReadWord(std::string& aString)
{
	SynchronizeGetPointer();

	if (CheckIfReadIsPossible())
	{
		if (IsBinary())
		{
			aString = "";
			char readChar = NULL;

			do
			{
				ReadData(&readChar, sizeof(char));
				aString += readChar;
			}
			while (readChar != NULL
				&& readChar != mySpaceCharacter);
		}
		else
		{
			aString = "";
			char readChar = mySpaceCharacter;
			myFileStream.get(readChar);

			while (readChar != myEndLineCharacter
				   && readChar != mySpaceCharacter)
			{
				aString += readChar;
				myFileStream.get(readChar);
			}
		}
		return myFileStream.good();
	}
	return false;
}

bool FS::File::ReadString(std::string& aString)
{
	SynchronizeGetPointer();

	if (CheckIfReadIsPossible())
	{
		if (IsBinary())
		{
			aString = "";
			char readChar = NULL;
			
			do
			{
				ReadData(&readChar, sizeof(char));
				aString += readChar;
			}
			while (readChar != NULL);
		}
		else
		{
			aString = "";
			char readChar = mySpaceCharacter;
			myFileStream.get(readChar);

			while (readChar != myEndLineCharacter)
			{
				aString += readChar;
				myFileStream.get(readChar);

				if (myFileStream.good() == false)
				{
					return false;
				}
			}
		}
		return myFileStream.good();
	}
	return false;
}

bool FS::File::WriteString(std::string aString)
{
	SynchornizePutPointer();

	if (CheckIfWriteIsPossible())
	{
		if (IsBinary())
		{
			WriteData(&aString[0], sizeof(char)*(aString.size()+1));
		}
		else
		{
			myFileStream<<aString<<std::endl;
		}
		return myFileStream.good();
	}
	return false;
}

bool FS::File::WriteInt(int& aInteger)
{
	SynchornizePutPointer();

	if (CheckIfWriteIsPossible())
	{
		if (IsBinary())
		{
			WriteData(&aInteger, sizeof(int));
		}
		else
		{
			myFileStream<<aInteger<<std::endl;
		}
		return myFileStream.good();
	}
	return false;
}

bool FS::File::WriteFloat(float& aFloat)
{
	SynchornizePutPointer();

	if (CheckIfWriteIsPossible())
	{
		if (IsBinary())
		{
			WriteData(&aFloat, sizeof(float));
		}
		else
		{
			myFileStream.precision(myNumberOfFloatDecimalDigets);
			myFileStream<<aFloat<<std::endl;
		}
		return myFileStream.good();
	}
	return false;
}

bool FS::File::WriteDouble(double& aDouble)
{
	SynchornizePutPointer();

	if (CheckIfWriteIsPossible())
	{
		if (IsBinary())
		{
			WriteData(&aDouble, sizeof(double));
		}
		else
		{
			myFileStream.precision(myNumberOfDoubleDecimalDigets);
			myFileStream<<aDouble<<std::endl;
		}
		return myFileStream.good();
	}
	return false;
}

bool FS::File::WriteData(void* someData,int aSizeToRead)
{
	SynchornizePutPointer();

	if (CheckIfWriteIsPossible())
	{
		myFileStream.write(static_cast<const char*>(someData), aSizeToRead);
		return myFileStream.good();
	}
	return false;
}

bool FS::File::ReadData(void* someData,int aSizeToRead)
{
	SynchronizeGetPointer();

	if (CheckIfReadIsPossible())
	{
		myFileStream.read(static_cast<char*>(someData), aSizeToRead);
		return myFileStream.good();
	}
	return false;
}

int FS::File::GetFileSize()
{
	long begin = myFileStream.tellg();
	myFileStream.seekg(0, std::ios::end);
	long end = myFileStream.tellg();
	myFileStream.seekp(0, std::ios::beg);
	myFileStream.seekg(0, std::ios::beg);
	return (end-begin);
}

bool FS::File::FlushToDisk()
{
	if (myFileStream.is_open())
	{
		if (myFlags.test(WRITE))
		{
			myFileStream.flush();
			return myFileStream.good();
		}
	}
	return false;
}

void FS::File::SynchornizePutPointer()
{
	if (myLastActionWasReading == true)
	{
		myLastActionWasReading = false;
		myLastActionWasWriting = true;

		if (myFlags.test(APPEND) == false)
		{
			myFileStream.seekp(0, std::ios_base::end);
		}
		else
		{
			myFileStream.seekp(0, std::ios_base::beg);
		}
	}
}

void FS::File::SynchronizeGetPointer()
{
	if (myLastActionWasWriting == true)
	{
		myLastActionWasReading = true;
		myLastActionWasWriting = false;
		FlushToDisk();
		myFileStream.seekg(0, std::ios_base::beg);
	}
}

bool FS::File::CheckIfWriteIsPossible()
{
	if (myFileStream.is_open())
	{
		if (myFlags.test(WRITE))
		{
			return myFileStream.good();
		}
	}
	return false;
}

bool FS::File::CheckIfReadIsPossible()
{
	if (myFileStream.is_open())
	{
		if (myFlags.test(READ))
		{
			return myFileStream.good();
		}
	}
	return false;
}