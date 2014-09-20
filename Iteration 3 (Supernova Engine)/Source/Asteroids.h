#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "Engine.h"
#include "Game Objects/ProjectileSystem.h"
#include "Game Objects/SpaceShipSystem.h"
#include "Game Objects/AsteroidSystem.h"
#include "Game Objects/ExplosionSystem.h"
#include "Game Objects/CollisionSystem.h"
#include "Game Objects/ScoreSystem.h"

class Asteroids : public Engine {
public:
	Asteroids();
	virtual ~Asteroids();

	virtual bool init();
	virtual void start();
	virtual void stop();

	void startGame(int numberOfPlayers);
	void resumeGame();

	virtual void reset();
	virtual void update(unsigned int timeElapsed);
	virtual void draw();

	virtual bool handleCommand(const char * command);

	void displayFrameRate();
	void displayInfo();

public:
	static Asteroids * instance;

protected:
	ProjectileSystem m_projectileSystem;
	SpaceShipSystem m_spaceShipSystem;
	AsteroidSystem m_asteroidSystem;
	ExplosionSystem m_explosionSystem;
	CollisionSystem m_collisionSystem;
	ScoreSystem m_scoreSystem;

	Sound * m_music;
};

#endif // ASTEROIDS_H
