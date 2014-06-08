#include "Game.h"

const int Game::maxPlayers = 4;

Game::Game(Variables * settings,
		   HINSTANCE hInstance,
		   WNDPROC WndProc,
		   LPCTSTR winClassName,
		   LPCTSTR title,
		   int nCmdShow)
			: playerScores(NULL),
			  playerScoreText2P(NULL),
			  playerScoreText3P(NULL),
			  playerScoreText4P(NULL),
			  playerColours(NULL),
			  numberOfPlayers(1),
			  mainMenu(NULL),
			  mainMenuActive(true),
			  helpItemOffset(250),
			  helpItemIncrement(55),
			  helpScreenActive(false),
			  leftMouseButtonPressed(false),
			  rightMouseButtonPressed(false),
			  spaceBarPressed(false),
			  menuUpKeyPressed(false),
			  menuDownKeyPressed(false),
			  menuSelectKeyPressed(false),
			  escapeKeyPressed(false),
			  directInput(NULL),
			  keyboard(NULL),
			  mouse(NULL),
			  d3d(NULL),
			  d3dDevice(NULL) {
    // verify and initialize game settings parsed from settings file
	this->settings = settings;
	if(!verifySettings(settings)) {
		quit("Error", "Settings file is invalid.");
	}

	this->windowPosX = atoi(settings->getValue("Window Position Horizontal"));
	this->windowPosY = atoi(settings->getValue("Window Position Vertical"));
	this->windowWidth = atoi(settings->getValue("Window Width"));
	this->windowHeight = atoi(settings->getValue("Window Height"));
	
	// initialize directx and directinput
	if(!init(hInstance, WndProc, winClassName, title, nCmdShow)) {
		quit("Error", "Error initializing game.");
	}

	// initialize player data (scores, colours, etc.)
	this->playerScores = new int[maxPlayers];
	this->playerScoreText2P = new Text*[2];
	this->playerScoreText3P = new Text*[3];
	this->playerScoreText4P = new Text*[4];
	this->playerColours = new D3DCOLOR[maxPlayers];
	this->playerColours[0] = D3DCOLOR_RGBA(255, 0, 0, 255); // red
	this->playerColours[1] = D3DCOLOR_RGBA(0, 0, 255, 255); // blue
	this->playerColours[2] = D3DCOLOR_RGBA(0, 255, 0, 255); // green
	this->playerColours[3] = D3DCOLOR_RGBA(255, 255, 0, 255); // yellow

	for(int i=0;i<maxPlayers;i++) {
		playerScores[i] = 0;
	}

	char * fontFace = "Arial";
	int fontSize = 18;
	int fontWeight = Text::BOLD;
	bool fontItalic = false;

	playerScoreText2P[0] = new Text(fontFace, fontSize, fontWeight, fontItalic, Text::RIGHT, Text::LEFT, (int) (windowWidth / 2.0f) - 4, 0, playerColours[0], d3dDevice);
	playerScoreText2P[1] = new Text(fontFace, fontSize, fontWeight, fontItalic, Text::LEFT, Text::RIGHT, (int) (windowWidth / 2.0f) + 5, 0, playerColours[1], d3dDevice);

	playerScoreText3P[0] = new Text(fontFace, fontSize, fontWeight, fontItalic, Text::RIGHT, Text::LEFT, (int) (windowWidth / 2.0f) - 14, 0, playerColours[0], d3dDevice);
	playerScoreText3P[1] = new Text(fontFace, fontSize, fontWeight, fontItalic, Text::CENTER, Text::CENTER, (int) (windowWidth / 2.0f), 0, playerColours[1], d3dDevice);
	playerScoreText3P[2] = new Text(fontFace, fontSize, fontWeight, fontItalic, Text::LEFT, Text::RIGHT, (int) (windowWidth / 2.0f) + 13, 0, playerColours[2], d3dDevice);

	playerScoreText4P[0] = new Text(fontFace, fontSize, fontWeight, fontItalic, Text::RIGHT, Text::LEFT, (int) (windowWidth / 2.0f) - 22, 0, playerColours[0], d3dDevice);
	playerScoreText4P[1] = new Text(fontFace, fontSize, fontWeight, fontItalic, Text::RIGHT, Text::LEFT, (int) (windowWidth / 2.0f) - 4, 0, playerColours[1], d3dDevice);
	playerScoreText4P[2] = new Text(fontFace, fontSize, fontWeight, fontItalic, Text::LEFT, Text::RIGHT, (int) (windowWidth / 2.0f) + 5, 0, playerColours[2], d3dDevice);
	playerScoreText4P[3] = new Text(fontFace, fontSize, fontWeight, fontItalic, Text::LEFT, Text::RIGHT, (int) (windowWidth / 2.0f) + 23, 0, playerColours[3], d3dDevice);

	// load sound effects
	explosionSound = new Sound("Explosion.wav", settings->getValue("Sound Directory"));
	laserSound = new Sound("Laser.wav", settings->getValue("Sound Directory"));
	
	// load and parse sprite sheet
	spriteSheetTexture = new Sprite("Asteroids.png", settings->getValue("Sprite Directory"), d3dDevice);

	// sprite sheet offsets
	int _sx, _sy, _lx, _ly, _bx, _by, _ex, _ey;
	int _rs = 43, _ri = _rs + 2;
	int _lw = 3, _lh = 9, _li = _lw + 2;
	int _bw = 6, _bh = 15, _bi = _bw + 2;
	int _es = 55, _ei = _es + 2;
	SpriteSheetOffset spriteSheetOffsets[] = {
		// red space ship sprites (index 0)
		{_sx=1,	     _sy=1,	   _rs, _rs}, // idle
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx-=_ri*2, _sy+=_ri, _rs, _rs}, // moving 1
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx-=_ri*2, _sy+=_ri, _rs, _rs}, // moving 2
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx+=_ri,   _sy,	   _rs, _rs},
		// blue space ship sprites (index 9)
		{_sx=1,	     _sy=136,  _rs, _rs}, // idle
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx-=_ri*2, _sy+=_ri, _rs, _rs}, // moving 1
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx-=_ri*2, _sy+=_ri, _rs, _rs}, // moving 2
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx+=_ri,   _sy,	   _rs, _rs},
		// green space ship sprites (index 18)
		{_sx=378,    _sy=1,	   _rs, _rs}, // idle
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx-=_ri*2, _sy+=_ri, _rs, _rs}, // moving 1
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx-=_ri*2, _sy+=_ri, _rs, _rs}, // moving 2
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx+=_ri,   _sy,	   _rs, _rs},
		// yellow space ship sprites (index 27)
		{_sx=378,    _sy=136,  _rs, _rs}, // idle
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx-=_ri*2, _sy+=_ri, _rs, _rs}, // moving 1
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx-=_ri*2, _sy+=_ri, _rs, _rs}, // moving 2
		{_sx+=_ri,   _sy,	   _rs, _rs},
		{_sx+=_ri,   _sy,	   _rs, _rs},
		// asteroid sprites (index 36)
		{136, 1,  55, 55}, // big asteroids
		{193, 1,  48, 48},
		{193, 51, 31, 31}, // smal asteroids
		{136, 58, 26, 26},
		{164, 58, 21, 21},
		{226, 51, 12, 12},
		// laser sprites (index 42)
		{_lx=192, _ly=85, _lw, _lh}, // red
		{_lx+=_li, _ly,	  _lw, _lh},
		{_lx+=_li, _ly,	  _lw, _lh}, // blue
		{_lx+=_li, _ly,	  _lw, _lh},
		{_lx+=_li, _ly,	  _lw, _lh}, // green
		{_lx+=_li, _ly,	  _lw, _lh},
		{_lx+=_li, _ly,	  _lw, _lh}, // yellow
		{_lx+=_li, _ly,	  _lw, _lh},
		// bomb sprites (index 50)
		{_bx=136,  _by=86, _bw, _bh},
		{_bx+=_bi, _by,	   _bw, _bh},
		{_bx+=_bi, _by,	   _bw, _bh},
		{_bx+=_bi, _by,	   _bw, _bh},
		{_bx+=_bi, _by,	   _bw, _bh},
		{_bx+=_bi, _by,	   _bw, _bh},
		{_bx+=_bi, _by,	   _bw, _bh},
		// explosion sprites (index 57)
		{_ex=136,  _ey=103, _es, _es},
		{_ex+=_ei, _ey,	    _es, _es},
		{_ex+=_ei, _ey,	    _es, _es},
		{_ex+=_ei, _ey,	    _es, _es}
	};
	spriteSheet = new SpriteSheet(spriteSheetTexture, spriteSheetOffsets, 61);

	// initialize player space ships
	this->spaceShips = new SpaceShip*[maxPlayers];
	spaceShips[0] = new SpaceShip(windowWidth * 0.2f, windowHeight * 0.2f, 135, windowWidth, windowHeight, spriteSheet, 0, spriteSheet->getSprite(42), laserSound, d3dDevice);
	spaceShips[1] = new SpaceShip(windowWidth * 0.8f, windowHeight * 0.8f, -45, windowWidth, windowHeight, spriteSheet, 9, spriteSheet->getSprite(44), laserSound, d3dDevice);
	spaceShips[2] = new SpaceShip(windowWidth * 0.2f, windowHeight * 0.8f, 45, windowWidth, windowHeight, spriteSheet, 18, spriteSheet->getSprite(46), laserSound, d3dDevice);
	spaceShips[3] = new SpaceShip(windowWidth * 0.8f, windowHeight * 0.2f, -135, windowWidth, windowHeight, spriteSheet, 27, spriteSheet->getSprite(48), laserSound, d3dDevice);

	resetAsteroids();

	// create the main menu
	mainMenu = new Menu("Main Menu", windowWidth, windowHeight, d3dDevice);
	mainMenu->addMenuItem("1 Player", d3dDevice);
	mainMenu->addMenuItem("2 Players", d3dDevice);
	mainMenu->addMenuItem("Help", d3dDevice);
	mainMenu->addMenuItem("Quit", d3dDevice);

	// create the help screen
	helpTitleText = new Text("System", 136, Text::BOLD, false, Text::CENTER, Text::CENTER, (int) (windowWidth / 2.0f), 100, D3DCOLOR_RGBA(255, 0, 0, 255), d3dDevice);
	helpItemMessages.push_back("P1 Controls: WSAD to move/turn, Left Ctrl/Space to shoot.");
	helpItemMessages.push_back("P2 Controls: Arrow Keys to move/turn, Right Ctrl/Enter to shoot.");
	helpItemMessages.push_back("Escape to return to main menu / quit.");
	for(unsigned int i=0;i<helpItemMessages.size();i++) {
		helpItemText.push_back(new Text("System", 42, Text::BOLD, false, Text::CENTER, Text::CENTER, (int) (windowWidth / 2.0f),  helpItemOffset + (i * helpItemIncrement), D3DCOLOR_RGBA(170, 0, 0, 255), d3dDevice));
	}

	// used for test drawing sprites from spitesheet (t = toggle)
	#if _DEBUG
		testDrawSprites = 0;
	#endif
}

Game::~Game() {
	unsigned int i;
	if(settings != NULL) { delete settings; }
	for(int i=0;i<maxPlayers;i++) { delete spaceShips[i]; }
	delete [] spaceShips;
	for(i=0;i<asteroids.size();i++) { if(asteroids.at(i) != NULL) { delete asteroids.at(i); } }
	if(spriteSheet != NULL) { delete spriteSheet; }
	if(spriteSheetTexture != NULL) { delete spriteSheetTexture; }
	if(explosionSound != NULL) { delete explosionSound; }
	if(laserSound != NULL) { delete laserSound; }
	if(playerScores != NULL) { delete [] playerScores; }
	if(playerColours != NULL) { delete [] playerColours; }
	if(playerScoreText2P != NULL) {
		for(int i=0;i<2;i++) { if(playerScoreText2P[i] != NULL) { delete playerScoreText2P[i]; } }
		delete [] playerScoreText2P;
	}
	if(playerScoreText3P != NULL) {
		for(int i=0;i<3;i++) { if(playerScoreText3P[i] != NULL) { delete playerScoreText3P[i]; } }
		delete [] playerScoreText3P;
	}
	if(playerScoreText4P != NULL) {
		for(int i=0;i<4;i++) { if(playerScoreText4P[i] != NULL) { delete playerScoreText4P[i]; } }
		delete [] playerScoreText4P;
	}
	delete mainMenu;
	delete helpTitleText;
	if(keyboard != NULL) { keyboard->Unacquire(); keyboard->Release(); }
	if(mouse != NULL) { mouse->Unacquire(); mouse->Release(); }
	if(directInput != NULL) { directInput->Release(); }
	if(d3dDevice != NULL) { d3dDevice->Release(); }
	if(d3d != NULL) { d3d->Release(); }
}

void Game::setNumberOfPlayers(int numberOfPlayers) {
	this->numberOfPlayers = numberOfPlayers;
}

void Game::tick() {
	processKeyboardInput();
	processMouseInput();
	
	for(unsigned int i=0;i<asteroids.size();i++) {
		// update asteroids
		asteroids.at(i)->tick();

		// check asteroid > asteroid collision
		for(unsigned int j=0;j<asteroids.size();j++) {
			if(i != j && asteroids.at(i)->checkCollision(*asteroids.at(j))) {
				handleCollision(*asteroids.at(i), *asteroids.at(j));
			}
		}
	}

	for(int p=0;p<numberOfPlayers;p++) {
		// update ships
		spaceShips[p]->tick();

		// check ship > ship collision
		for(int k=0;k<numberOfPlayers;k++) {
			if(p != k && spaceShips[p]->checkCollision(*spaceShips[k])) {
				spawnExplosion(*spaceShips[p]);
				spawnExplosion(*spaceShips[k]);

				spaceShips[p]->reset(true);
				spaceShips[k]->reset(true);

				reset(false);
			}
		}

		for(unsigned int i=0;i<asteroids.size();i++) {
			// check ship > asteroid collision
			if(spaceShips[p]->checkCollision(*asteroids.at(i))) {
				spawnExplosion(*spaceShips[p]);
				spaceShips[p]->reset(false);

				reset(false);
				return;
			}

			for(unsigned int j=0;j<spaceShips[p]->projectiles.size();j++) {
				// check projectile > ship collision
				for(int k=0;k<numberOfPlayers;k++) {
					if(k != p && spaceShips[p]->projectiles.at(j)->checkCollision(*spaceShips[k])) {
						// create an explosion and reset the loser's ship
						spawnExplosion(*spaceShips[k]);
						spaceShips[k]->reset(false);

						// increase the victor's score
						playerScores[p]++;
						
						// remove the projectile that hit the ship and decrement
						delete spaceShips[p]->projectiles.at(j);
						spaceShips[p]->projectiles.erase(spaceShips[p]->projectiles.begin() + j);

						j--;

						reset(false);
						return;
					}
				}
			}

			for(unsigned int j=0;j<spaceShips[p]->projectiles.size();j++) {

				// check projectile > asteroid collision
				if(spaceShips[p]->projectiles.at(j)->checkCollision(*asteroids.at(i))) {
					// [potentially] create a cluster of smaller asteroids if this was a big asteroid
					if(asteroids.at(i)->isBigAsteroid()) {
						spawnAsteroidClusterFrom(*asteroids.at(i));
					}

					// spawn an explosion in place of the asteroid
					spawnExplosion(*asteroids.at(i));
					
					// remove the asteroid that was destroyed
					delete asteroids.at(i);
					asteroids.erase(asteroids.begin() + i);

					// remove the projectile that hit the asteroid
					delete spaceShips[p]->projectiles.at(j);
					spaceShips[p]->projectiles.erase(spaceShips[p]->projectiles.begin() + j);

					i--;
					j--;

					break;
				}
			}
		}
	}

	for(unsigned int i=0;i<explosions.size();i++) {
		// update explosions
		explosions.at(i)->tick();
		if(explosions.at(i)->done()) {
			// if an explosion has finished its animation sequence, remove it
			delete explosions.at(i);
			explosions.erase(explosions.begin() + i);

			i--;
		}
	}

	// primitive asteroid respawn code
	int numberOfBigAsteroids;
	do {
		// calculate the number of big asteroids
		numberOfBigAsteroids = 0;
		for(unsigned int i=0;i<asteroids.size();i++) {
			numberOfBigAsteroids += (asteroids.at(i)->isBigAsteroid() ? 1 : 0);
		}

		// if there is less than 10 big asteroids on the screen, continue spawning asteroids until there are
		if(numberOfBigAsteroids < 10) {
			for(int i=0;i<10-numberOfBigAsteroids;i++) {
				spawnAsteroid();
			}
		}
	} while(numberOfBigAsteroids < 10);
}

void Game::draw() {
	unsigned int i;

	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	
	d3dDevice->BeginScene();

	// draw the asteroids
	for(i=0;i<asteroids.size();i++) {
		asteroids.at(i)->draw(d3dDevice);
	}

	// draw the space ships
	for(int i=0;i<numberOfPlayers;i++) {
		spaceShips[i]->draw(d3dDevice);
	}

	// draw the explosions
	for(unsigned int i=0;i<explosions.size();i++) {
		explosions.at(i)->draw(d3dDevice);
	}

	// draw the player scores at the top of the screen (if there is more than one player)
	if(numberOfPlayers == 2) {
		for(int i=0;i<2;i++) {
			playerScoreText2P[i]->draw("%d", playerScores[i]);
		}
	}
	else if(numberOfPlayers == 3) {
		for(int i=0;i<3;i++) {
			playerScoreText3P[i]->draw("%d", playerScores[i]);
		}
	}
	else if(numberOfPlayers == 4) {
		for(int i=0;i<4;i++) {
			playerScoreText4P[i]->draw("%d", playerScores[i]);
		}
	}
	
	// if running under debug mode, display sprite tests (if enabled via t)
	#if _DEBUG
		float drawSpriteOffsetX = 1.0f;
		float drawSpriteOffsetY = 1.0f;
		float drawSpriteScale = 4.0f;
		int drawShipIndexOffset = (testDrawSprites-1) * 9;
		// test draw ships
		if(testDrawSprites >= 1 && testDrawSprites <= 4) {
			drawSpriteScale = 4.0f;
			for(int i=0;i<9;i++) {
				D3DXVECTOR2 scale(drawSpriteScale, drawSpriteScale);
				D3DXVECTOR2 offset((spriteSheet->getSprite(i + drawShipIndexOffset)->getWidth() * drawSpriteScale) / 2.0f, (spriteSheet->getSprite(i + drawShipIndexOffset)->getHeight() * drawSpriteScale) / 2.0f);
				D3DXVECTOR2 position(drawSpriteOffsetX + (offset.x * drawSpriteScale), drawSpriteOffsetY + (offset.y * drawSpriteScale));
				spriteSheet->getSprite(i + drawShipIndexOffset)->draw(&scale, &offset, 0, NULL, &position, d3dDevice);
				drawSpriteOffsetX += (spriteSheet->getSprite(i + drawShipIndexOffset)->getWidth() * drawSpriteScale) + drawSpriteScale;
				if(i == 2 || i == 5) {
					drawSpriteOffsetX = 1;
					drawSpriteOffsetY += (spriteSheet->getSprite(i + drawShipIndexOffset)->getHeight() * drawSpriteScale) + drawSpriteScale;
				}
			}
		}
		// test draw asteroids
		else if(testDrawSprites == 5) {
			drawSpriteScale = 4.0f;
			for(int i=36;i<42;i++) {
				D3DXVECTOR2 scale(drawSpriteScale, drawSpriteScale);
				D3DXVECTOR2 offset((spriteSheet->getSprite(i)->getWidth() * drawSpriteScale) / 2.0f, (spriteSheet->getSprite(i)->getHeight() * drawSpriteScale) / 2.0f);
				D3DXVECTOR2 position(drawSpriteOffsetX + (offset.x * drawSpriteScale), drawSpriteOffsetY + (offset.y * drawSpriteScale));
				spriteSheet->getSprite(i)->draw(&scale, &offset, 0, NULL, &position, d3dDevice);
				drawSpriteOffsetX += (spriteSheet->getSprite(i)->getWidth() * drawSpriteScale) + drawSpriteScale + 100;
				if(i == 38) {
					drawSpriteOffsetX = 1;
					drawSpriteOffsetY += (spriteSheet->getSprite(9)->getHeight() * drawSpriteScale) + drawSpriteScale + 200;
				}
			}
		}
		// test draw lasers
		else if(testDrawSprites == 6) {
			drawSpriteScale = 4.0f;
			for(int i=42;i<50;i++) {
				D3DXVECTOR2 scale(drawSpriteScale, drawSpriteScale);
				D3DXVECTOR2 offset((spriteSheet->getSprite(i)->getWidth() * drawSpriteScale) / 2.0f, (spriteSheet->getSprite(i)->getHeight() * drawSpriteScale) / 2.0f);
				D3DXVECTOR2 position(drawSpriteOffsetX + (offset.x * drawSpriteScale), drawSpriteOffsetY + (offset.y * drawSpriteScale));
				spriteSheet->getSprite(i)->draw(&scale, &offset, 0, NULL, &position, d3dDevice);
				drawSpriteOffsetX += (spriteSheet->getSprite(i)->getWidth() * drawSpriteScale) + drawSpriteScale;
			}
		}
		// test draw bombs
		else if(testDrawSprites == 7) {
			drawSpriteScale = 4.0f;
			for(int i=50;i<57;i++) {
				D3DXVECTOR2 scale(drawSpriteScale, drawSpriteScale);
				D3DXVECTOR2 offset((spriteSheet->getSprite(i)->getWidth() * drawSpriteScale) / 2.0f, (spriteSheet->getSprite(i)->getHeight() * drawSpriteScale) / 2.0f);
				D3DXVECTOR2 position(drawSpriteOffsetX + (offset.x * drawSpriteScale), drawSpriteOffsetY + (offset.y * drawSpriteScale));
				spriteSheet->getSprite(i)->draw(&scale, &offset, 0, NULL, &position, d3dDevice);
				drawSpriteOffsetX += (spriteSheet->getSprite(i)->getWidth() * drawSpriteScale) + drawSpriteScale;
			}
		}
		// test draw explosions
		else if(testDrawSprites == 8) {
			drawSpriteScale = 3.0f;
			for(int i=57;i<61;i++) {
				D3DXVECTOR2 scale(drawSpriteScale, drawSpriteScale);
				D3DXVECTOR2 offset((spriteSheet->getSprite(i)->getWidth() * drawSpriteScale) / 2.0f, (spriteSheet->getSprite(i)->getHeight() * drawSpriteScale) / 2.0f);
				D3DXVECTOR2 position(drawSpriteOffsetX + (offset.x * drawSpriteScale), drawSpriteOffsetY + (offset.y * drawSpriteScale));
				spriteSheet->getSprite(i)->draw(&scale, &offset, 0, NULL, &position, d3dDevice);
				drawSpriteOffsetX += (spriteSheet->getSprite(i)->getWidth() * drawSpriteScale) + drawSpriteScale;
			}
		}
	#endif

	d3dDevice->EndScene();
	
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Game::drawHelp() {
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	
	d3dDevice->BeginScene();

	// display help title
	helpTitleText->draw("Help");

	// display help items
	for(unsigned int i=0;i<helpItemText.size();i++) {
		helpItemText.at(i)->draw(helpItemMessages.at(i));
	}

	d3dDevice->EndScene();
	
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Game::reset(bool resetScores) {
	// reset scores if appropriate
	if(resetScores && numberOfPlayers > 1) {
		for(int i=0;i<maxPlayers;i++) {
 			playerScores[i] = 0;
		}
	}

	// reset ship positions
	if(numberOfPlayers == 1) {
		spaceShips[0]->resetToCenter(true);
	}
	else {
		for(int i=0;i<numberOfPlayers;i++) {
			spaceShips[i]->reset(true);
		}
	}

	// re-populate the screen with a new set of asteroids
	resetAsteroids();
}

int Game::run() {
    MSG msg;
	DWORD elapsedTime = 0;
	DWORD currentTime = 0;
	
    while(true) {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if(msg.message == WM_QUIT) {
                break;
			}
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		
		// if the main menu/help is active, only draw it, and process input
		if(mainMenuActive) {
			processKeyboardInput();

			if(helpScreenActive) {
				drawHelp();
			}
			else {
				mainMenu->draw(d3dDevice);
			}
			
		}
		// otherwise, render the game
		else {
			tick();

			draw();
		}

		elapsedTime = (DWORD) (GetTickCount() - lastRenderTime);
		if(elapsedTime < timePerFrame) {
			Sleep((DWORD) (timePerFrame - elapsedTime));
		}
		lastRenderTime = GetTickCount();
    }
	
    return msg.wParam;
}

void Game::spawnAsteroid() {
	int asteroidIndex;
	bool bigAsteroid;
	if((rand() % 100) < 30) {
		// spawn small asteroid (30% chance)
		asteroidIndex = (rand() % 4) + 38;
		bigAsteroid = false;
	}
	else {
		// spawn big asteroid (70% chance)
		asteroidIndex = (rand() % 2) + 36;
		bigAsteroid = true;
	}

	bool isInsideOfAsteroid;
	bool isTooCloseToShip;
	Asteroid * newAsteroid = new Asteroid(windowWidth, windowHeight, spriteSheet->getSprite(asteroidIndex), bigAsteroid);
	do {
		// make sure that the new asteroid is not too close to a space ship
		isTooCloseToShip = false;
		for(int i=0;i<numberOfPlayers;i++) {
			if(spaceShips[i]->checkExtendedCollision(*newAsteroid)) {
				isTooCloseToShip = true;
			}
		}

		// also make sure that the asteroid is not stuck inside of another asteroid
		isInsideOfAsteroid = false;
		if(!isTooCloseToShip) {
			for(unsigned int i=0;i<asteroids.size();i++) {
				if(asteroids.at(i)->checkCollision(*newAsteroid)) {
					isInsideOfAsteroid = true;
				}
			}
		}

		// if it is too close to a ship or inside of another asteroid, then re-randomize its position until it isn't
		if(isTooCloseToShip || isInsideOfAsteroid) {
			newAsteroid->randomizePosition();
		}
	} while(isTooCloseToShip || isInsideOfAsteroid);
	asteroids.push_back(newAsteroid);
}

void Game::spawnAsteroidClusterFrom(Asteroid & a) {
	int clusterSize = 0;
	int clusterSeed = rand() % 100;
		 if(clusterSeed <   9) { clusterSize = 0; } //  9% chance no asteroids
	else if(clusterSeed <  28) { clusterSize = 1; } // 19% chance 1 asteroid
	else if(clusterSeed <  66) { clusterSize = 2; } // 38% chance 2 asteroids
	else if(clusterSeed <  93) { clusterSize = 3; } // 27% chance 3 asteroids
	else if(clusterSeed < 100) { clusterSize = 4; } //  7% chance 4 asteroids

	// create the corresponding number of mini-asteroids, and set their appropriate locations and directions
	// by rotating a pair of x/y co-ordinates around the origin of the original asteroid, randomized at equal
	// intervals and set their velocities so they are moving away from the origin of the original asteroid
	float angle = (float) (rand() % 360);
	float angleIncrement = (360.0f / clusterSize);
	Asteroid * newAsteroid;
	for(int i=0;i<clusterSize;i++) {
		newAsteroid = new Asteroid(windowWidth, windowHeight, spriteSheet->getSprite((rand() % 4) + 38), false);

		// calculate the velocities of the new asteroid
		float minVelocity = ((rand() % (int) (0.3 * 10000)) / 10000.0f) + 0.007f;
		float maxVelocity = ((rand() % (int) (1.8 * 10000)) / 10000.0f) + 0.8f;
		float xVelocity = ((rand() % (int) ((maxVelocity - minVelocity) * 10000)) / 10000.0f) + minVelocity;
		float yVelocity = ((rand() % (int) ((maxVelocity - minVelocity) * 10000)) / 10000.0f) + minVelocity;

		// set the velocities and locations of the new asteroid
		newAsteroid->setPosition(a.getX() + (a.getRadiusX() * cos(D3DXToRadian(angle))), a.getY() + (a.getRadiusY() * sin(D3DXToRadian(angle))));
		newAsteroid->setVelocity(xVelocity * cos(D3DXToRadian(angle)), yVelocity * sin(D3DXToRadian(angle)));

		asteroids.push_back(newAsteroid);

		// increment to the next projection angle
		angle += angleIncrement;
	}
}

void Game::spawnExplosion(Object & o) {
	// create a new explosion and begin playing the explosion sound
	explosions.push_back(new Explosion(o.getX() - o.getRadiusX(), o.getY() - o.getRadiusY(), o.getVelocityX(), o.getVelocityY(), o.getOrientation(), windowWidth, windowHeight, spriteSheet, 57, d3dDevice));
	explosionSound->play();
}

void Game::resetAsteroids() {
	// remove all of the asteroids
	for(unsigned int i=0;i<asteroids.size();i++) {
		delete asteroids.at(i);
		asteroids.erase(asteroids.begin() + i);

		i--;
	}

	// spawn between 8 and 12 asteroids on the screen
	for(int i=0;i<(rand() % 5) + 8;i++) {
		spawnAsteroid();
	}
}

void Game::handleCollision(Object & o1, Object & o2) {
	double v = o1.getVelocity();
		
	double dx = abs( o2.getX() - o1.getX() );
	double dy = abs( o1.getY() - o2.getY() );
	double d = sqrt( pow(dx, 2) + pow(dy, 2) );
	if(d == 0)
		return;
	
	double angle_b = asin(dy / d);
	double angle_d = asin( abs(o1.getVelocityX()) / v );
	double angle_a = (3.14159265 / 2.0f) - angle_b - angle_d;
	double angle_c = angle_b - angle_a;
	
	double v1, v2;
	
	v1 = v * abs( sin(angle_a) );
	v2 = v * abs( cos(angle_a) );
	
	double v1x = v1 * abs( cos(angle_c) );
	double v1y = v1 * abs( sin(angle_c) );
	double v2x = v2 * abs( cos(angle_b) );
	double v2y = v2 * abs( sin(angle_b) );
	
	if(o1.getVelocityX() > 0) {
		if( o1.getX() < o2.getX() )
			v1x = -v1x;
		else
			v2x = -v2x;
	}
	else {
		if( o1.getX() > o2.getX() )
			v2x = -v2x;
		else
			v1x = -v1x;
	}
	
	if(o1.getVelocityY() > 0) {
		if( o1.getY() < o2.getY() )
			v1y = -v1y;
		else
			v2y = -v2y;
	}
	else {
		if( o1.getY() > o2.getY() )
			v2y = -v2y;
		else
			v1y = -v1y;
	}

	o1.setVelocity((float) v1x, (float) v1y);
	o2.setVelocity((float) v2x, (float) v2y);
 }

bool Game::verifySettings(Variables * settings) {
	// verify that the settings file has the required values
	return	settings->hasValue("Sprite Directory") &&
			settings->hasValue("Sound Directory") &&
			settings->hasValue("Window Width") &&
			settings->hasValue("Window Height");
}

bool Game::init(HINSTANCE hInstance, WNDPROC WndProc, LPCTSTR winClassName, LPCTSTR title, int nCmdShow) {
	// initialize the window
	this->hInstance = hInstance;
	this->fps = 60;
	this->timePerFrame = 1000 / fps;
	
	if(!RegisterWndClass(hInstance, WndProc, winClassName)) {
		MessageBoxA(NULL, "Could not register class.", "Error", MB_OK);
		return false;
	}
	
	// create the window
	hWnd = CreateWindow(winClassName, title, WS_OVERLAPPEDWINDOW, windowPosX, windowPosY, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);
	
	if(hWnd == NULL) {
		MessageBoxA(NULL, "Could not create window.", "Error", MB_OK);
		return false;
	}
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// initialize directx
	D3DPRESENT_PARAMETERS d3dpp;
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if(d3d == NULL) { return false; }
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = windowWidth;
	d3dpp.BackBufferHeight = windowHeight;
	d3dpp.Windowed = true;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	if(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3dDevice) != S_OK) {
		return false;
	}
	
	// initialize directinput
	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **) &directInput, NULL);
	if(directInput == NULL) { return false; }
	
	if(directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL) != S_OK) { return false; }
	if(keyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) != DI_OK) { return false; }
	if(keyboard->SetDataFormat(&c_dfDIKeyboard) != DI_OK) { return false; }
	
	if(directInput->CreateDevice(GUID_SysMouse, &mouse, NULL) != DI_OK) { return false; }
	if(mouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND) != DI_OK) { return false; }
	if(mouse->SetDataFormat(&c_dfDIMouse) != DI_OK) { return false; }

	return true;
}

bool Game::RegisterWndClass(HINSTANCE hInstance, WNDPROC WndProc, LPCTSTR winClassName) {
	WNDCLASS wc;
	
	wc.style		 = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName  = NULL;
	wc.lpfnWndProc	 = WndProc;
	wc.lpszClassName = winClassName;
	wc.hIcon = NULL;
	
	if(RegisterClass(&wc) == 0) {
		return false;
	}
	
	return true;
}

void Game::processKeyboardInput() {
	// if the window is not in focus, do not do anything
	if(!GetFocus()) { return; }

	// get the state of the keyboard keys
	int result;
	while((result = keyboard->GetDeviceState(256, keyboardState)) != DI_OK) {
		switch(result) {
			case DI_OK:
				break;
			case DIERR_INPUTLOST:
			case DIERR_NOTACQUIRED:
				keyboard->Acquire();
				break;
			case E_PENDING:
				break;
			case DIERR_INVALIDPARAM:
			case DIERR_NOTINITIALIZED:
			default:
				return;
		}
	}
	
	// escape (display menu / go to previous menu / quit - depending on current state)
	if(keyboardState[DIK_ESCAPE] & 0x80) {
		if(!escapeKeyPressed) {
			if(helpScreenActive) {
				helpScreenActive = false;
			}
			else if(!mainMenuActive) {
				mainMenuActive = true;
			}
			else {
				PostQuitMessage(0);
			}
		}
		escapeKeyPressed = true;
	}
	else {
		escapeKeyPressed = false;
	}

	// if main menu is active
	if(mainMenuActive) {
		// handle menu selection
		if(keyboardState[DIK_RETURN] & 0x80 || keyboardState[DIK_SPACE] & 0x80) {
			if(!menuSelectKeyPressed) {
				switch(mainMenu->getIndex()) {\
					// start game in single player mode
					case 0:
						setNumberOfPlayers(1);
						reset(true);
						mainMenuActive = false;
						break;
					// start game in 2 player mode
					case 1:
						setNumberOfPlayers(2);
						reset(true);
						mainMenuActive = false;
						break;
					// display help screen
					case 2:
						helpScreenActive = true;
						break;
					// quit the game
					case 3:
						PostQuitMessage(0);
						break;
				}
			}
			menuSelectKeyPressed = true;
		}
		else { menuSelectKeyPressed = false; }

		// if the help screen is active, the player should not be able to change their position in the menu
		if(helpScreenActive) { return; }

		// move menu selection up
		if(keyboardState[DIK_UP] & 0x80 || keyboardState[DIK_W] & 0x80) {
			if(!menuUpKeyPressed) {
				mainMenu->moveUp();
			}
			menuUpKeyPressed = true;
		}
		else { menuUpKeyPressed = false; }

		// move menu selection down
		if(keyboardState[DIK_DOWN] & 0x80 || keyboardState[DIK_S] & 0x80) {
			if(!menuDownKeyPressed) {
				mainMenu->moveDown();
			}
			menuDownKeyPressed = true;
		}
		else { menuDownKeyPressed = false; }

		// do not process game input (space ship controls) - the game is not running
		return;
	}
	
	// reset animation identifiers for each player's space ship
	for(int i=0;i<numberOfPlayers;i++) {
		spaceShips[i]->isMoving = false;
		spaceShips[i]->isRotating = 0;
	}

	// move forward (player 1)
	if(keyboardState[DIK_W] & 0x80 ||
	   (numberOfPlayers == 1 && keyboardState[DIK_UP] & 0x80)) { // use P2 controls for 1P mode
		spaceShips[0]->moveForwards();
		spaceShips[0]->isMoving = true;
	}

	// move backwards (player 1)
	if(keyboardState[DIK_S] & 0x80 ||
	   (numberOfPlayers == 1 && keyboardState[DIK_DOWN] & 0x80)) { // use P2 controls for 1P mode
		spaceShips[0]->moveBackwards();
		spaceShips[0]->isMoving = true;
	}

	// turn left (player 1)
	if(keyboardState[DIK_A] & 0x80 ||
	   (numberOfPlayers == 1 && keyboardState[DIK_LEFT] & 0x80)) { // use P2 controls for 1P mode
		spaceShips[0]->turnLeft();
		if(spaceShips[0]->isRotating > 0) { spaceShips[0]->isRotating = 0; }
		else { spaceShips[0]->isRotating = -1; }
	}
	
	// turn right (player 1)
	if(keyboardState[DIK_D] & 0x80 ||
	   (numberOfPlayers == 1 && keyboardState[DIK_RIGHT] & 0x80)) { // use P2 controls for 1P mode
		spaceShips[0]->turnRight();
		if(spaceShips[0]->isRotating < 0) { spaceShips[0]->isRotating = 0; }
		else { spaceShips[0]->isRotating = 1; }
	}

	//fire laser (player 1)
	if(keyboardState[DIK_SPACE] & 0x80 || keyboardState[DIK_LCONTROL] & 0x80 ||
	   (numberOfPlayers == 1 && (keyboardState[DIK_RETURN] & 0x80 || keyboardState[DIK_RCONTROL] & 0x80))) { // use p2 controls for 1p mode
		if(!spaceBarPressed) {
			spaceShips[0]->fireLaser();
		}
		spaceBarPressed = true;
	}
	else { spaceBarPressed = false; }

	// move forwards (player 2)
	if(keyboardState[DIK_UP] & 0x80) {
		if(numberOfPlayers >= 2) {
			spaceShips[1]->moveForwards();
			spaceShips[1]->isMoving = true;
		}
	}
	
	// move backwards (player 2)
	if(keyboardState[DIK_DOWN] & 0x80) {
		if(numberOfPlayers >= 2) {
			spaceShips[1]->moveBackwards();
			spaceShips[1]->isMoving = true;
		}
	}

	// turn left (player 2)
	if(keyboardState[DIK_LEFT] & 0x80) {
		if(numberOfPlayers >= 2) {
			spaceShips[1]->turnLeft();
			if(spaceShips[1]->isRotating > 0) { spaceShips[1]->isRotating = 0; }
			else { spaceShips[1]->isRotating = -1; }
		}
	}
	
	// turn right (player 2)
	if(keyboardState[DIK_RIGHT] & 0x80) {
		if(numberOfPlayers >= 2) {
			spaceShips[1]->turnRight();
			if(spaceShips[1]->isRotating < 0) { spaceShips[1]->isRotating = 0; }
			else { spaceShips[1]->isRotating = 1; }
		}
	}

	// fire laser (player 2)
	if(keyboardState[DIK_RETURN] & 0x80 || keyboardState[DIK_RCONTROL] & 0x80) {
		if(!enterKeyPressed) {
			if(numberOfPlayers >= 2) {
				spaceShips[1]->fireLaser();
			}
		}
		enterKeyPressed = true;
	}
	else { enterKeyPressed = false; }

	// if debugging, allow t to toggle test sprite drawing
	#if _DEBUG
		if(keyboardState[DIK_T] & 0x80) {
			if(!testDrawSpritesKeyDown) {
				testDrawSprites++;
				if(testDrawSprites > 8) { testDrawSprites = 0; }
			}
			testDrawSpritesKeyDown = true;
		}
		else {
			testDrawSpritesKeyDown = false;
		}
	#endif
}

void Game::processMouseInput() {
	// if the window is not in focus, don't do anything
	if(!GetFocus()) { return; }

	// get the state of the mouse
	int result;
	while((result = mouse->GetDeviceState(sizeof(DIMOUSESTATE), (void *) &mouseState)) != DI_OK) {
		switch(result) {
			case DI_OK:
				break;
			case DIERR_INPUTLOST:
			case DIERR_NOTACQUIRED:
				mouse->Acquire();
				break;
			case E_PENDING:
				break;
			case DIERR_INVALIDPARAM:
			case DIERR_NOTINITIALIZED:
			default:
				return;
		}
	}

	POINT pt;
	RECT wRec;

	// if the left mouse button is pressed
	if(mouseState.rgbButtons[0] & 0x80) {
		if(!leftMouseButtonPressed) {
			GetCursorPos(&pt); 
			ScreenToClient(hWnd, &pt);
			GetWindowRect(hWnd, &wRec); 

			// and the cursor is inside the window
			if(pt.x >= wRec.left && pt.x <= wRec.right && pt.y >= wRec.top && pt.y <= wRec.bottom) {
				// fire the laser from player 1's ship
				spaceShips[0]->fireLaser();
			}
		}
		leftMouseButtonPressed = true;
	}
	else {
		leftMouseButtonPressed = false;
	}

	// if the right mouse button is pressed
	if(mouseState.rgbButtons[1] & 0x80) {
		if(!rightMouseButtonPressed) {
			GetCursorPos(&pt); 
			ScreenToClient(hWnd, &pt);
			GetWindowRect(hWnd, &wRec); 

			// and the cursor is inside the window
			if(pt.x >= wRec.left && pt.x <= wRec.right && pt.y >= wRec.top && pt.y <= wRec.bottom) {
				for(unsigned int i=0;i<asteroids.size();i++) {
					// change the rotation direction of all the asteroids on the screen
					asteroids.at(i)->changeRotationDirection();
				}
			}
		}
		rightMouseButtonPressed = true;
	}
	else {
		rightMouseButtonPressed = false;
	}
}
