#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <cocos2d.h>
#include "Utilities/Utilities.h"
#include "SpriteAnimationSystem/SpriteAnimationCollection.h"
#include "GameSystems/ProjectileSystem.h"
#include "GameSystems/SpaceShipSystem.h"

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
};

#endif // ASTEROIDS_H
