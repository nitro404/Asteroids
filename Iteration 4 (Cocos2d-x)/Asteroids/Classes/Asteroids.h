#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <cocos2d.h>
#include "Utilities/Utilities.h"
#include "SpriteAnimationSystem/SpriteAnimationCollection.h"

using namespace cocos2d;

class Asteroids : public cocos2d::Layer {
public:
	static Scene * createScene();
	virtual bool init();
	void menuCloseCallback(Ref * pSender);
	CREATE_FUNC(Asteroids);

protected:
	SpriteAnimationCollection * m_animations;
};

#endif // ASTEROIDS_H
