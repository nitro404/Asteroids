#include "Main.h"

// if debugging, display memory leaks from Virtual Leak Detector and the built in leak checker
#if _DEBUG
	#include <vld.h>
	#include <crtdbg.h>
	void checkForLeaks() {
		_CrtDumpMemoryLeaks();
	}
#endif

// program entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	#if _DEBUG
		atexit(checkForLeaks);
	#endif

	srand((unsigned int) time(NULL));

	// read settings file
	Variables * settings = new Variables();
	if(!settings->parseFrom("settings.ini")) {
		delete settings;
		quit("Error", "Could not find the settings file \"settings.ini\".");
	}

	// create and run the game
	Game game = Game(settings, hInstance, WndProc, L"game", L"Asteroids", nCmdShow);
	game.run();

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch(message) {
        case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
            break;
    }
	
    return DefWindowProc(hWnd, message, wParam, lParam);
}
