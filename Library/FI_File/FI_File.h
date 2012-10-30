#ifndef _FILE_WRAPPER_H_
#define _FILE_WRAPPER_H_
#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <sstream>
#include <limits>

namespace FileSystem
{
	inline char GetNewLineCharacterForSystem()
	{
		std::stringstream ss;
		ss<<std::endl;
		return ss.str().c_str()[0];
	}

	class File
	{
	public:
		enum FileFlags
		{
			READ,
			WRITE,
			APPEND,
			BINARY
		};
	public:
		File(void);
		~File(void);
		bool Open(std::string aFileName, std::bitset<8> aSetOfFlags=0xF);
		bool Close();
		bool GoToNewLine(); // Changing row in the code should not work for binary files.

		bool ReadInt(int& aInteger);
		bool ReadFloat(float& aFloat);
		bool ReadDouble(double& aDouble);
		bool WriteInt(int& aInteger);
		bool WriteFloat(float& aFloat);
		bool WriteDouble(double& aDouble);

		bool ReadWord(std::string& aString);
		bool ReadString(std::string& aString);
		bool WriteString(std::string aString);

		bool WriteData(void* someData,int aSizeToRead);
		bool ReadData(void* someData,int aSizeToRead);

		int GetFileSize();

		bool FlushToDisk(); // Flush to make sure all data is written to disk
	private:
		std::fstream::open_mode SetFlagsInOpeningParameters(std::bitset<8> aSetOfFlags);
		void SynchornizePutPointer();
		void SynchronizeGetPointer();
		bool CheckIfWriteIsPossible();
		bool CheckIfReadIsPossible();
		inline bool File::IsBinary()
		{
			return myFlags.test(BINARY);
		}
	private:
		static const int    myNumberOfDoubleDecimalDigets = std::numeric_limits<double>::digits10 + 1;
		static const int	myNumberOfFloatDecimalDigets = std::numeric_limits<float>::digits10 + 1;
		static const char   mySpaceCharacter;
		static const char	myEndLineCharacter;
		std::fstream		myFileStream;
		std::bitset<8>		myFlags;
		bool				myLastActionWasReading;
		bool				myLastActionWasWriting;
	};
}

namespace FS = FileSystem;

#endif