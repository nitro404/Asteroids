#pragma once

#include "Includes.h"
#include "Variables.h"
#include "Menu.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Text.h"
#include "Sound.h"
#include "Object.h"
#include "SpaceShip.h"
#include "Asteroid.h"
#include "Projectile.h"
#include "Explosion.h"

// the main game engine and all its functionality
class Game {
public:
	Game(Variables * settings, HINSTANCE hInstance, WNDPROC WndProc, LPCTSTR winClassName, LPCTSTR title, int nCmdShow);
	~Game();
	
	void processKeyboardInput();
	void processMouseInput();

	void setNumberOfPlayers(int numberOfPlayers); // change the number of players
	
	void tick(); // update the game state
	void draw(); // draw the play area
	void drawHelp(); // draw help screen
	void reset(bool resetScores); // reset the play area
	int run(); // run the game
	
private:
	void spawnAsteroid(); // spawn a random asteroid
	void spawnAsteroidClusterFrom(Asteroid & a); // spawn a random cluster of asteroids from an already-existing asteroid which has been destroyed
	void spawnExplosion(Object & o); // create an explosion on an object
	void resetAsteroids(); // clears all of the asteroids and replaces them with a new set
	void handleCollision(Object & o1, Object & o2); // handle a collision between two asteroids

	bool init(HINSTANCE hInstance, WNDPROC WndProc, LPCTSTR winClassName, LPCTSTR title, int nCmdShow);
	bool RegisterWndClass(HINSTANCE hInstance, WNDPROC WndProc, LPCTSTR winClassName);

	bool verifySettings(Variables * settings); // verify integrity of settings file (has required values)

public:
	// window position / dimensions
	int windowPosX, windowPosY;
	int windowWidth, windowHeight;

	// settings file data
	Variables * settings;

private:
	// objects
	SpaceShip ** spaceShips;
	vector<Asteroid *> asteroids;
	vector<Explosion *> explosions;

	// sprite sheet
	Sprite * spriteSheetTexture;
	SpriteSheet * spriteSheet;

	// sound effects
	Sound * explosionSound;
	Sound * laserSound;

	// menu data
	Menu * mainMenu;
	bool mainMenuActive;
	Text * helpTitleText;
	vector<char *> helpItemMessages;
	vector<Text *> helpItemText;
	int helpItemOffset;
	int helpItemIncrement;
	bool helpScreenActive;

	// player data
	int numberOfPlayers;
	const static int maxPlayers;
	int * playerScores;
	Text ** playerScoreText2P;
	Text ** playerScoreText3P;
	Text ** playerScoreText4P;
	D3DCOLOR * playerColours;

	// input locking semaphores
	bool leftMouseButtonPressed;
	bool rightMouseButtonPressed;
	bool spaceBarPressed;
	bool enterKeyPressed;
	bool menuUpKeyPressed;
	bool menuDownKeyPressed;
	bool menuSelectKeyPressed;
	bool escapeKeyPressed;

	// window handles
	HINSTANCE hInstance;
	HWND hWnd;

	// directinput handles
	LPDIRECTINPUT8 directInput;
	LPDIRECTINPUTDEVICE8 keyboard;
	LPDIRECTINPUTDEVICE8 mouse;
	char keyboardState[256];
	DIMOUSESTATE mouseState;
	
	// directx handles
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3dDevice;
	
	// fps data
	time_t lastRenderTime;
	int fps;
	time_t timePerFrame;

	// debug testing
	#if _DEBUG
		int testDrawSprites;
		bool testDrawSpritesKeyDown;
	#endif
};
