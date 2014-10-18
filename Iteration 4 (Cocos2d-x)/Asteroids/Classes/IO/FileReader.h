#ifndef FILE_READER_H
#define FILE_READER_H

#include "Utilities/Utilities.h"
#include "IO/FileReaderMode.h"

class FileReader {
public:
	FileReader(const char * fileName = NULL, bool openFile = false);
	FileReader(const std::string & fileName, bool openFile = false);
	virtual ~FileReader();

	const std::string & getFileName() const;

	bool isOpen() const;
	bool endOfFile() const;
	bool open(const char * fileName = NULL);
	bool open(const std::string & fileName);
	void close();

	const std::string & readLine();

	bool operator == (const FileReader & f) const;
	bool operator != (const FileReader & f) const;

protected:
	std::string m_fileName;
	bool m_open;
	FILE * m_file;
	std::string m_data;
	int m_index;
	FileReaderModes::FileReaderMode m_mode;
	std::string m_line;
};

#endif // FILE_READER_H
