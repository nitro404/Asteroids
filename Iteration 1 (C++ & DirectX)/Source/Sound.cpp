#include "Sound.h"

Sound::Sound(const char * fileName, const char * directory) {
	// initialize the sound file path and store it
	string soundFilePath;
	soundFilePath.append(directory);
	if(_stricmp(soundFilePath.substr(soundFilePath.length() - 1, soundFilePath.length()).c_str(), ("\\")) != 0 &&
	   _stricmp(soundFilePath.substr(soundFilePath.length() - 1, soundFilePath.length()).c_str(), ("/")) != 0) {
		soundFilePath.append("\\");
	}
	soundFilePath.append(fileName);
	this->fileName = new char[strlen(soundFilePath.c_str()) + 1];
	strcpy_s(this->fileName, strlen(soundFilePath.c_str()) + 1, soundFilePath.c_str());
}

Sound::Sound(const char * fileName) {
	// initialize the sound file path and store it
	this->fileName = new char[strlen(fileName) + 1];
	strcpy_s(this->fileName, strlen(fileName) + 1, fileName);
}

Sound::~Sound() {
	delete [] fileName;
}

void Sound::play() {
	// play the sound once
	USES_CONVERSION;
	PlaySound(A2W(fileName), NULL, SND_FILENAME | SND_ASYNC);
}

void Sound::loop() {
	// loop the sound
	USES_CONVERSION;
	PlaySound(A2W(fileName), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void Sound::stop() {
	// stop the sound
	PlaySound(NULL, NULL, SND_ASYNC);
}
