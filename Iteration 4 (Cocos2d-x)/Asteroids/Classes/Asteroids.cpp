#include "Asteroids.h"

Scene * Asteroids::createScene() {
	auto scene = Scene::create();
	auto layer = Asteroids::create();
	scene->addChild(layer);
	return scene;
}

bool Asteroids::init() {
	if(!Layer::init()) { return false; }

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Asteroids.plist", "Asteroids.png");

	m_animations = SpriteAnimationCollection::readFrom("Animations.ini");
	if(m_animations == NULL) { return false; }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size windowSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	const SpriteAnimation * explosionSpriteAnimation = m_animations->getAnimation("Explosion");
	Sprite * explosionSprite = explosionSpriteAnimation->getSprite();

	explosionSprite->setPosition(windowSize.width / 2, windowSize.height / 2);

	Action * explosionAction = RepeatForever::create(Animate::create(explosionSpriteAnimation->getAnimation()));
	explosionSprite->runAction(explosionAction);
	addChild(explosionSprite);

	return true;
}

void Asteroids::menuCloseCallback(Ref * pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
    return;
#endif

	if(m_animations != NULL) { delete m_animations; }

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
