#include "Asteroids.h"

Asteroids * Asteroids::instance(NULL);

Scene * Asteroids::createScene() {
	auto scene = Scene::create();
	auto layer = Asteroids::create();
	scene->addChild(layer);
	return scene;
}

Asteroids * Asteroids::getInstance() {
	return instance;
}

ProjectileSystem * Asteroids::getProjectileSystem() const {
	return m_projectileSystem;
}

SpaceShipSystem * Asteroids::getSpaceShipSystem() const {
	return m_spaceShipSystem;
}

AsteroidSystem * Asteroids::getAsteroidSystem() const {
	return m_asteroidSystem;
}

ExplosionSystem * Asteroids::getExplosionSystem() const {
	return m_explosionSystem;
}

ScoreSystem * Asteroids::getScoreSystem() const {
	return m_scoreSystem;
}

CollisionSystem * Asteroids::getCollisionSystem() const {
	return m_collisionSystem;
}

bool Asteroids::init() {
	if(!Layer::init()) { return false; }

	instance = this;

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

	m_spaceShipSystem->start(1);

	EventListenerKeyboard * keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = [] (EventKeyboard::KeyCode keyCode, Event * event) {
		if(!Asteroids::getInstance()->getSpaceShipSystem()->isStarted()) { return; }

		SpaceShip * spaceShip = const_cast<SpaceShip *>(Asteroids::getInstance()->getSpaceShipSystem()->getSpaceShip(0));

			 if(keyCode == EventKeyboard::KeyCode::KEY_W)		{ spaceShip->moveForward(true); }
		else if(keyCode == EventKeyboard::KeyCode::KEY_S)		{ spaceShip->moveBackward(true); }
		else if(keyCode == EventKeyboard::KeyCode::KEY_A)		{ spaceShip->turnLeft(true); }
		else if(keyCode == EventKeyboard::KeyCode::KEY_D)		{ spaceShip->turnRight(true); }
		else if(keyCode == EventKeyboard::KeyCode::KEY_SPACE)	{ spaceShip->fireLaser(true); }
	};

	keyboardListener->onKeyReleased = [] (EventKeyboard::KeyCode keyCode, Event * event) {
		if(!Asteroids::getInstance()->getSpaceShipSystem()->isStarted()) { return; }

		SpaceShip * spaceShip = const_cast<SpaceShip *>(Asteroids::getInstance()->getSpaceShipSystem()->getSpaceShip(0));

			 if(keyCode == EventKeyboard::KeyCode::KEY_W)		{ spaceShip->moveForward(false); }
		else if(keyCode == EventKeyboard::KeyCode::KEY_S)		{ spaceShip->moveBackward(false); }
		else if(keyCode == EventKeyboard::KeyCode::KEY_A)		{ spaceShip->turnLeft(false); }
		else if(keyCode == EventKeyboard::KeyCode::KEY_D)		{ spaceShip->turnRight(false); }
		else if(keyCode == EventKeyboard::KeyCode::KEY_SPACE)	{ spaceShip->fireLaser(false); }
	};

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	EventListenerTouchOneByOne * touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = [] (Touch * touch, Event * event) {
		if(!Asteroids::getInstance()->getSpaceShipSystem()->isStarted()) { return false; }

		SpaceShip * spaceShip = const_cast<SpaceShip *>(Asteroids::getInstance()->getSpaceShipSystem()->getSpaceShip(0));

		spaceShip->fireLaser(true);

		return true;
    };

	touchListener->onTouchMoved = [] (Touch * touch, Event * event) {
		if(!Asteroids::getInstance()->getSpaceShipSystem()->isStarted()) { return; }

		Size visibleDimensions = Director::getInstance()->getVisibleSize();

		SpaceShip * spaceShip = const_cast<SpaceShip *>(Asteroids::getInstance()->getSpaceShipSystem()->getSpaceShip(0));

		spaceShip->setPosition(spaceShip->x(), visibleDimensions.height - touch->getLocationInView().y);
    };

	touchListener->onTouchEnded = [=] (Touch * touch, Event * event) {
		if(!Asteroids::getInstance()->getSpaceShipSystem()->isStarted()) { return; }

		SpaceShip * spaceShip = const_cast<SpaceShip *>(Asteroids::getInstance()->getSpaceShipSystem()->getSpaceShip(0));

		spaceShip->fireLaser(false);
	};

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	schedule(schedule_selector(Asteroids::update)); 

	return true;
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
