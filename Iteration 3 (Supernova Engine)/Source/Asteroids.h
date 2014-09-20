#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "Engine.h"
#include "Game Systems/ProjectileSystem.h"
#include "Game Systems/SpaceShipSystem.h"
#include "Game Systems/AsteroidSystem.h"
#include "Game Systems/ExplosionSystem.h"
#include "Game Systems/CollisionSystem.h"
#include "Game Systems/ScoreSystem.h"

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
