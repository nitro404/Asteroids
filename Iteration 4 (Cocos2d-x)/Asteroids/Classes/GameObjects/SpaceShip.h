#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H

#include "SpriteAnimationSystem/SpriteAnimation.h"
#include "GameObjects/SpaceShipMovementDirection.h"
#include "GameObjects/SpaceShipColour.h"
#include "GameSystems/ProjectileSystem.h"

class SpaceShip : public AnimatedEntity2D {
public:
	SpaceShip(Layer * parent, const SpaceShipColours::SpaceShipColour colour, const std::vector<SpriteFrame *> & idleSpriteFrames, const std::vector<const SpriteAnimation *> & movementAnimations, ProjectileSystem * projectileSystem, const Vec2 & position = Vec2::ZERO, float rotation = 0.0f);
	SpaceShip(const SpaceShip & s);
	SpaceShip & operator = (const SpaceShip & s);
	virtual ~SpaceShip();

	int getIndex() const;
	SpaceShipColours::SpaceShipColour getColour() const;
	bool setColour(SpaceShipColours::SpaceShipColour colour);
	bool setColour(int colour);
	bool setColour(const char * data);
	bool setColour(const std::string & data);
	bool setColour(const Colour & colour);

	bool isEnabled();
	void setEnabled(bool enable = true);
	void enable();
	void disable();

	void moveForward(bool value = true);
	void moveBackward(bool value = true);
	void turnLeft(bool value = true);
	void turnRight(bool value = true);

	void fireLaser(bool value = true);

	bool checkMinimumSpawnRadius(const Entity2D & entity) const;
	bool checkMinimumSpawnRadius(const Vec2 & position, float size) const;

	virtual void reset();
	virtual void update(float timeElapsed);

	bool operator == (const SpaceShip & s) const;
	bool operator != (const SpaceShip & s) const;

private:
	void updateVelocity(float acceleration, float timeElapsed);

public:
	static const float spaceShipAcceleration;
	static const float maximumSpaceShipSpeed;
	static const float spaceShipRotationSpeed;
	static const float spaceShipSize;
	static const float laserRateOfFire;
	static const float projectileSpawnRadius;
	static const float minimumSpawnRadius;

private:
	bool m_enabled;
	bool m_enginesActive;
	bool m_moveForward;
	bool m_moveBackward;
	bool m_turnLeft;
	bool m_turnRight;
	bool m_fireLaser;

	bool m_initialLaserBeamSpawned;
	float m_fireLaserTimeElapsed;

	SpaceShipMovementDirections::SpaceShipMovementDirection m_movementDirection;
	SpaceShipColours::SpaceShipColour m_colour;

	std::vector<Sprite *> m_idleSprites;
	std::vector<SpriteAnimation *> m_movementAnimations;
	
	ProjectileSystem * m_projectileSystem;
};

#endif // SPACE_SHIP_H