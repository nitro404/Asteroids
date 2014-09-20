#include "Asteroids.h"

Asteroids * Asteroids::instance = NULL;

Asteroids::Asteroids()
	: m_music(NULL) {
	instance = this;

	m_settings->setSettingsFileName("Asteroids.ini");
}

Asteroids::~Asteroids() {
	if(m_settings != NULL) { m_settings->save(); }
}

bool Asteroids::init() {
	if(!Engine::init()) { return false; }
	
	setWindowTitle("Asteroids");
	
	m_menu->setTitle("Asteroids");
//	m_menu->addItem("New Game", "menu newgame");
	m_menu->addItem("1 Player", "game start 1");
	m_menu->addItem("2 Players", "game start 2");
	m_menu->addItem("3 Players", "game start 3");
	m_menu->addItem("4 Players", "game start 4");
	m_menu->addItem("Resume Game", "game resume");
	m_menu->addItem("Options", "menu options");
	m_menu->addItem("Help", "menu help");
	m_menu->addItem("Quit", "quit");

	m_menu->open();

	m_projectileSystem.init(m_resources, m_animations);
	m_spaceShipSystem.init(m_sprites, m_animations, &m_projectileSystem);
	m_asteroidSystem.init(m_sprites, &m_spaceShipSystem);
	m_explosionSystem.init(m_animations, m_resources);
	m_scoreSystem.init(m_resources, &m_spaceShipSystem);
	m_collisionSystem.init(&m_projectileSystem, &m_spaceShipSystem, &m_asteroidSystem, &m_explosionSystem, &m_scoreSystem);

	m_music = m_resources->getSound("Music");
	if(m_settings->music) {
		m_music->play();
	}

	return true;
}

void Asteroids::start() {
	Engine::start();
}

void Asteroids::stop() {
	Engine::stop();
}

void Asteroids::startGame(int numberOfPlayers) {
	if(!m_initialized) { return; }

	m_spaceShipSystem.start(numberOfPlayers);

	m_projectileSystem.reset();
	m_asteroidSystem.reset();
	m_scoreSystem.reset();

	m_menu->close();
}

void Asteroids::resumeGame() {
	if(!m_initialized || !m_spaceShipSystem.isStarted()) { return; }

	m_menu->close();
}

bool Asteroids::handleCommand(const char * command) {
	if(Engine::handleCommand(command)) { return true; }

	static const QRegExp   gameRegExp("^(game)$");

	static const QRegExp  startRegExp("^(start)$");
	static const QRegExp resumeRegExp("^(resume)$");

	static const QRegExp    oneRegExp("^(1|one)$");
	static const QRegExp    twoRegExp("^(2|two)$");
	static const QRegExp  threeRegExp("^(3|three)$");
	static const QRegExp   fourRegExp("^(4|four)$");

	QString commandName = Utilities::getCommand(command).toLower();
	if(commandName.isEmpty()) { return false; }
	QString arguments = Utilities::getArguments(command);

	if(gameRegExp.exactMatch(commandName)) {
		QString gameCommandName = Utilities::getCommand(arguments).toLower();
		if(gameCommandName.isEmpty()) { return false; }
		QString gameArguments = Utilities::getArguments(arguments);

		if(startRegExp.exactMatch(gameCommandName)) {
			QString numberOfPlayersData = Utilities::getCommand(gameArguments).toLower();
			if(numberOfPlayersData.isEmpty()) { return false; }

			int numberOfPlayers = -1;

				 if(  oneRegExp.exactMatch(numberOfPlayersData)) { numberOfPlayers = 1; }
			else if(  twoRegExp.exactMatch(numberOfPlayersData)) { numberOfPlayers = 2; }
			else if(threeRegExp.exactMatch(numberOfPlayersData)) { numberOfPlayers = 3; }
			else if( fourRegExp.exactMatch(numberOfPlayersData)) { numberOfPlayers = 4; }
			else { return false; }

			startGame(numberOfPlayers);

			return true;
		}
		else if(resumeRegExp.exactMatch(gameCommandName)) {
			resumeGame();

			return true;
		}
	}

	if(m_spaceShipSystem.isStarted() && !m_menu->isActive()) {
		if(m_spaceShipSystem.handleCommand(command)) {
			return true;
		}
	}
	
	return false;
}

void Asteroids::displayFrameRate() {
	static Font * font = m_resources->getFont("Console Font");

	if(m_settings->showFrameRate) {
		font->drawText(m_settings->windowWidth - (font->getHorizontalSpacing() * (7 + Utilities::intLength((int) m_frameRate))) - 2, 2, "%.2f FPS", m_frameRate);
	}
}

void Asteroids::displayInfo() {
	static Font * font = m_resources->getFont("Console Font");

	if(m_settings->showInfo) {
		font->drawText(0, font->getVerticalSpacing() * 0, "Vendor: %s", glGetString(GL_VENDOR));
		font->drawText(0, font->getVerticalSpacing() * 1, "Renderer: %s", glGetString(GL_RENDERER));
		font->drawText(0, font->getVerticalSpacing() * 2, "OpenGL Version: %s", glGetString(GL_VERSION));
		font->drawText(0, font->getVerticalSpacing() * 3, "GLSL Version Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	}
}

void Asteroids::reset() {
	if(!m_initialized) { return; }

	if(m_spaceShipSystem.isStarted() && !m_menu->isActive()) {
		m_spaceShipSystem.reset();
		m_projectileSystem.reset();
		m_asteroidSystem.reset();
		m_scoreSystem.reset();
	}
}

void Asteroids::update(unsigned int timeElapsed) {
	Engine::update(timeElapsed);

	if(m_spaceShipSystem.isStarted() && !m_menu->isActive()) {
		m_spaceShipSystem.update(timeElapsed);
		m_projectileSystem.update(timeElapsed);
		m_asteroidSystem.update(timeElapsed);
		m_explosionSystem.update(timeElapsed);
		m_collisionSystem.update(timeElapsed);
	}
}

void Asteroids::draw() {
	Engine::beginDraw();

	if(m_spaceShipSystem.isStarted()) {
		m_asteroidSystem.draw();
		m_projectileSystem.draw();
		m_explosionSystem.draw();
		m_spaceShipSystem.draw();
		m_scoreSystem.draw();
	}

	displayFrameRate();
	displayInfo();
	
	Engine::endDraw();
}
