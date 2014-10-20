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
	m_asteroidSystem = new AsteroidSystem(this);
	m_explosionSystem = new ExplosionSystem(this);
	m_scoreSystem = new ScoreSystem(this);
	m_collisionSystem = new CollisionSystem(this);

	m_projectileSystem->init(m_animations);
	m_spaceShipSystem->init(m_animations, m_projectileSystem);
	m_asteroidSystem->init(m_spaceShipSystem);
	m_explosionSystem->init(m_animations);
	m_scoreSystem->init(m_spaceShipSystem);
	m_collisionSystem->init(m_projectileSystem, m_spaceShipSystem, m_asteroidSystem, m_explosionSystem, m_scoreSystem);

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

	if(m_collisionSystem != NULL) { delete m_collisionSystem; }
	if(m_scoreSystem != NULL) { delete m_scoreSystem; }
	if(m_explosionSystem != NULL) { delete m_explosionSystem; }
	if(m_asteroidSystem != NULL) { delete m_asteroidSystem; }
	if(m_spaceShipSystem != NULL) { delete m_spaceShipSystem; }
	if(m_projectileSystem != NULL) { delete m_projectileSystem; }
	
	if(m_animations != NULL) { delete m_animations; }
	
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
