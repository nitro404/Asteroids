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
	if(m_animations == NULL) {
		MessageBox("Failed to load animation definition file!", "Init Failed");
		return false;
	}

	m_projectileSystem = new ProjectileSystem(this);
	m_spaceShipSystem = new SpaceShipSystem(this);

	m_projectileSystem->init(m_animations);
	m_spaceShipSystem->init(m_animations, m_projectileSystem);

	m_spaceShipSystem->start(4);

	schedule(schedule_selector(Asteroids::update)); 

	return true;
}

void Asteroids::onEnter() {
	Layer::onEnter();
}

void Asteroids::onExit() {
	Layer::onExit();
}

bool Asteroids::onTouchBegan(Touch * touch, Event * event) {
	return Layer::onTouchBegan(touch, event);
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
