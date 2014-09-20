#ifndef SPACE_SHIP_SYSTEM_H
#define SPACE_SHIP_SYSTEM_H

#include <QVector.h>
#include "Entity/Entity.h"
#include "Game Objects/SpaceShip.h"
#include "Sprite Animation System/SpriteAnimationCollection.h"

class SpaceShipSystem : public Entity {
public:
	SpaceShipSystem();
	SpaceShipSystem(const SpaceShipSystem & s);
	SpaceShipSystem & operator = (const SpaceShipSystem & s);
	virtual ~SpaceShipSystem();

	int numberOfSpaceShips() const;
	const SpaceShip * getSpaceShip(int index) const;

	bool init(SpriteSheetCollection * spriteSheets, SpriteAnimationCollection * animations, ProjectileSystem * projectileSystem);
	bool start(int numberOfPlayers);
	bool isStarted() const;

	virtual void reset();
	bool handleCommand(const char * command);
	virtual void update(unsigned int timeElapsed);
	virtual void draw();

	bool operator == (const SpaceShipSystem & s) const;
	bool operator != (const SpaceShipSystem & s) const;

public:
	static const int maxNumberOfSpaceShips;

private:
	bool m_initialized;
	int m_numberOfSpaceShips;

	static const char * spriteSheetName;
	static const char * spriteName;

	QVector<const Sprite *> m_idleSprites[SpaceShipColours::NumberOfColours];
	QVector<const SpriteAnimation *> m_movementAnimations[SpaceShipColours::NumberOfColours];

	QVector<SpaceShip *> m_spaceShips;

};

#endif // SPACE_SHIP_SYSTEM_H
