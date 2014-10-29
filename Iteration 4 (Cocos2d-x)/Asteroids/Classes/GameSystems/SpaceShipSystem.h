#ifndef SPACE_SHIP_SYSTEM_H
#define SPACE_SHIP_SYSTEM_H

#include "Entity/Entity.h"
#include "GameObjects/SpaceShip.h"
#include "SpriteAnimationSystem/SpriteAnimationCollection.h"

class SpaceShipSystem : public Entity, public Component {
public:
	SpaceShipSystem(Layer * parentLayer);
	SpaceShipSystem(const SpaceShipSystem & s);
	SpaceShipSystem & operator = (const SpaceShipSystem & s);
	virtual ~SpaceShipSystem();

	int numberOfSpaceShips() const;
	const SpaceShip * getSpaceShip(int index) const;

	virtual Layer * getParentLayer() const;
	virtual void setParentLayer(Layer * parent);

	bool init(SpriteAnimationCollection * animations, ProjectileSystem * projectileSystem);
	bool start(int numberOfPlayers);
	bool isStarted() const;

	virtual void reset();
	bool handleCommand(const char * command);
	virtual void update(float timeElapsed);

	bool operator == (const SpaceShipSystem & s) const;
	bool operator != (const SpaceShipSystem & s) const;

public:
	static const char * spaceShipSystemClassName;
	static const int maxNumberOfSpaceShips;

private:
	bool m_initialized;
	int m_numberOfSpaceShips;

	static const char * spriteSheetName;
	static const char * spriteName;

	std::vector<SpriteFrame *> m_idleSpriteFrames[SpaceShipColours::NumberOfColours];
	std::vector<const SpriteAnimation *> m_movementAnimations[SpaceShipColours::NumberOfColours];

	std::vector<SpaceShip *> m_spaceShips;

};

#endif // SPACE_SHIP_SYSTEM_H
