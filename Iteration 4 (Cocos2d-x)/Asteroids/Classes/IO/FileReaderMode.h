#ifndef FILE_READER_MODE_H
#define FILE_READER_MODE_H

#include "Utilities/Utilities.h"

namespace FileReaderModes {
	enum FileReaderMode {
		Invalid = -1,
		Text,
		Binary,
		NumberOfFileReaderModes
	};
	
	extern const char * fileReaderModeStrings[];
	extern const FileReaderMode defaultFileReaderMode;
	
	bool isValid(FileReaderMode mode);
	bool isValid(int mode);
	const char * toString(FileReaderMode mode);
	const char * toString(int mode);
	FileReaderMode parseFrom(const char * data);
	FileReaderMode parseFrom(const std::string & data);
}

#endif // FILE_READER_MODE_H
