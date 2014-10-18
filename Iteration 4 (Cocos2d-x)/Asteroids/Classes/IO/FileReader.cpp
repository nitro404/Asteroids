#include "IO/FileReader.h"

FileReader::FileReader(const char * fileName, bool openFile)
	: m_fileName(Utilities::trimString(std::string(fileName)))
	, m_open(false)
	, m_file(NULL)
	, m_data()
	, m_index(0)
	, m_mode(FileReaderModes::Invalid)
	, m_line() {
	if(openFile) {
		open(m_fileName);
	}
}

FileReader::FileReader(const std::string & fileName, bool openFile)
	: m_fileName(Utilities::trimString(fileName))
	, m_open(false)
	, m_file(NULL)
	, m_data()
	, m_index(0)
	, m_mode(FileReaderModes::Invalid)
	, m_line() {
	if(openFile) {
		open(m_fileName);
	}
}

FileReader::~FileReader() {
	if(m_open) { close(); }
}

const std::string & FileReader::getFileName() const {
	return m_fileName;
}

bool FileReader::isOpen() const {
	return m_open;
}

bool FileReader::endOfFile()  const {
	if(!m_open) { return true; }

	if(m_mode == FileReaderModes::Text) {
		if(m_file == NULL || feof(m_file)) { return true; }
	}
	else {
		return m_index >= static_cast<int>(m_data.length());
	}
	return false;
}

bool FileReader::open(const char * fileName) {
	if(fileName == NULL || Utilities::stringLength(fileName) == 0) {
		if(m_open) {
			return true;
		}
		else {
			if(m_fileName.empty()) {
				return false;
			}
			else {
				return open(std::string());
			}
		}
	}
	
	return open(std::string(fileName));
}

bool FileReader::open(const std::string & fileName) {
	if(fileName.empty()) {
		if(m_open) {
			return true;
		}
		else {
			if(m_fileName.empty()) {
				return false;
			}
		}
	}
	else {
		if(Utilities::compareStringsIgnoreCase(m_fileName, fileName) == 0) {
			if(m_open) {
				return true;
			}
		}
		else {
			if(m_open) {
				close();
			}
			
			m_fileName = Utilities::trimString(fileName);
		}
	}

	std::string fullFilePath = FileUtils::getInstance()->fullPathForFilename(m_fileName);

	m_file = fopen(fullFilePath.data(), "r");
	if(m_file != NULL) {
		m_open = true;
		m_mode = FileReaderModes::Text;

		return true;
	}
	else {
		Data compressedData = FileUtils::getInstance()->getDataFromFile(fullFilePath);
		if(compressedData.isNull() || compressedData.getSize() <= 0) { return false; }

		const unsigned char * bytes = compressedData.getBytes();
		ssize_t dataLength = compressedData.getSize();
        
		unsigned char * unpackedData = nullptr;
		ssize_t unpackedDataLength = 0;
        
		if(ZipUtils::isCCZBuffer(bytes, dataLength)) {
			unpackedDataLength = ZipUtils::inflateCCZBuffer(bytes, dataLength, &unpackedData);
		}
		else if(ZipUtils::isGZipBuffer(bytes, dataLength)) {
			unpackedDataLength = ZipUtils::inflateMemory(const_cast<unsigned char*>(bytes), dataLength, &unpackedData);
		}
		else {
			unpackedData = const_cast<unsigned char*>(bytes);
			unpackedDataLength = dataLength;
		}

		char * tempData = new char[unpackedDataLength];

		for(int i=0;i<unpackedDataLength;i++) {
			tempData[i] = static_cast<char>(unpackedData[i]);
		}

		m_data = std::string(tempData);

		delete [] tempData;

		m_open = true;
		m_mode = FileReaderModes::Binary;

		return true;
	}

	return false;
}

void FileReader::close() {
	if(!m_open) { return; }

	if(m_mode == FileReaderModes::Text) {
		if(m_file != NULL) {
			fclose(m_file);
			m_file = NULL;
		}
	}
	else if(m_mode == FileReaderModes::Binary) {
		m_data.clear();
		m_index = 0;
	}

	m_line.clear();
	m_mode = FileReaderModes::Invalid;
	m_open = false;
}

const std::string & FileReader::readLine() {
	static char buffer[512];

	if(!m_open) {
		m_line.clear();
		return m_line;
	}

	if(m_mode == FileReaderModes::Text) {
		if(m_file == NULL) {
			m_line.clear();
			return m_line;
		}
		else {
			fgets(buffer, 256, m_file);
			m_line = Utilities::trimString(std::string(buffer), false, true);
			if(endOfFile()) {
				m_line.clear();
			}
			return m_line;
		}
	}
	else if(m_mode == FileReaderModes::Binary) {
		if(m_index >= static_cast<int>(m_data.length())) {
			m_line.clear();
			return m_line;
		}

		int end = -1;
		int nextIndex = -1;
		for(int i=m_index;i<static_cast<int>(m_data.length());i++) {
			if(m_data[i] == '\n') {
				if(i + 1 < static_cast<int>(m_data.length()) && m_data[i + 1] == '\r') {
					nextIndex++;
				}

				end = i;

				break;
			}
			else if(m_data[i] == '\r') {
				nextIndex = i + 1;

				if(i + 1 < static_cast<int>(m_data.length()) && m_data[i + 1] == '\n') {
					nextIndex++;
				}

				end = i;

				break;
			}
		}

		if(end < 1) {
			m_line = Utilities::substring(m_data, m_index, static_cast<int>(m_data.length()));
		}
		else {
			m_line = Utilities::substring(m_data, m_index, end);
		}

		m_index = nextIndex;
	}

	return m_line;
}

bool FileReader::operator == (const FileReader & f) const {
	return Utilities::compareStringsIgnoreCase(m_fileName, f.m_fileName) == 0;
}

bool FileReader::operator != (const FileReader & f) const {
	return !operator == (f);
}
