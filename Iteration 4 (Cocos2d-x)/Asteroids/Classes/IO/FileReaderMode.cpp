#include "IO/FileReaderMode.h"

const char * FileReaderModes::fileReaderModeStrings[] = { "Text", "Binary" };
const FileReaderModes::FileReaderMode FileReaderModes::defaultFileReaderMode = FileReaderModes::Text;

bool FileReaderModes::isValid(FileReaderMode mode) {
	return mode > Invalid && mode < NumberOfFileReaderModes;
}

bool FileReaderModes::isValid(int mode) {
	return mode > static_cast<int>(Invalid) && mode < static_cast<int>(NumberOfFileReaderModes);
}

const char * FileReaderModes::toString(FileReaderMode mode) {
	return toString(static_cast<int>(mode));
}

const char * FileReaderModes::toString(int mode) {
	if(!isValid(mode)) { return "Invalid"; }

	return fileReaderModeStrings[mode];
}

FileReaderModes::FileReaderMode FileReaderModes::parseFrom(const char * data) {
	if(data == NULL) { return Invalid; }

	FileReaderMode mode = Invalid;

	std::string modeString = Utilities::trimString(std::string(data));

	for(int i=0;i<static_cast<int>(NumberOfFileReaderModes);i++) {
		if(Utilities::compareStringsIgnoreCase(modeString.data(), fileReaderModeStrings[i]) == 0) {
			mode = static_cast<FileReaderMode>(i);
			break;
		}
	}

	return mode;
}

FileReaderModes::FileReaderMode FileReaderModes::parseFrom(const std::string & data) {
	return parseFrom(data.data());
}
