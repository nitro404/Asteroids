#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <cocos2d.h>
#include "Utilities/Utilities.h"
#include "SpriteAnimationSystem/SpriteAnimationCollection.h"
#include "GameSystems/ProjectileSystem.h"
#include "GameSystems/SpaceShipSystem.h"
#include "GameSystems/AsteroidSystem.h"
#include "GameSystems/ExplosionSystem.h"
#include "GameSystems/ScoreSystem.h"
#include "GameSystems/CollisionSystem.h"

using namespace cocos2d;

class Asteroids : public Layer {
public:
	static Scene * createScene();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	bool onTouchBegan(Touch * touch, Event * event);
	void menuCloseCallback(Ref * pSender);
	CREATE_FUNC(Asteroids);

protected:
	SpriteAnimationCollection * m_animations;

	ProjectileSystem * m_projectileSystem;
	SpaceShipSystem * m_spaceShipSystem;
	AsteroidSystem * m_asteroidSystem;
	ExplosionSystem * m_explosionSystem;
	ScoreSystem * m_scoreSystem;
	CollisionSystem * m_collisionSystem;
};

#endif // ASTEROIDS_H
