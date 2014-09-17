#pragma once

#include "Includes.h"
#include <mmsystem.h>
#include <process.h>

#pragma comment(lib, "winmm.lib")

// simple sound abstraction for playing audio files
class Sound {
public:
	Sound(const char * fileName, const char * directory);
	Sound(const char * fileName);
	~Sound();

	void play(); // play a sound once
	void loop(); // loop a sound indefinitely
	void stop(); // stop the sound from playing

private:
	char * fileName;
};
