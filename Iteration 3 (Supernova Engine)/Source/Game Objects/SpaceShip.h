#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H

#include "Sprite Animation System/SpriteAnimation.h"
#include "Entity/AnimatedEntity2D.h"
#include "Game Objects/SpaceShipMovementDirection.h"
#include "Game Objects/SpaceShipColour.h"
#include "Game Objects/ProjectileSystem.h"

class SpaceShip : public AnimatedEntity2D {
public:
	SpaceShip(const SpaceShipColours::SpaceShipColour colour, const QVector<const Sprite *> & idleSprites, const QVector<const SpriteAnimation *> & movementAnimations, ProjectileSystem * projectileSystem, const Vector2 & position = Vector2::Zero, float rotation = 0.0f);
	SpaceShip(const SpaceShip & s);
	SpaceShip & operator = (const SpaceShip & s);
	virtual ~SpaceShip();

	int getIndex() const;
	SpaceShipColours::SpaceShipColour getColour() const;
	bool setColour(SpaceShipColours::SpaceShipColour colour);
	bool setColour(int colour);
	bool setColour(const char * data);
	bool setColour(const QString & data);
	bool setColour(const Colour & colour);

	void moveForward(bool value = true);
	void moveBackward(bool value = true);
	void turnLeft(bool value = true);
	void turnRight(bool value = true);

	void fireLaser(bool value = true);

	bool checkMinimumSpawnRadius(const Entity2D & entity) const;
	bool checkMinimumSpawnRadius(const Vector2 & position, float size) const;

	virtual void reset();
	virtual void update(unsigned int timeElapsed);

	bool operator == (const SpaceShip & s) const;
	bool operator != (const SpaceShip & s) const;

private:
	void updateVelocity(float acceleration, unsigned int timeElapsed);

public:
	static const float spaceShipAcceleration;
	static const float maximumSpaceShipSpeed;
	static const float spaceShipRotationSpeed;
	static const float spaceShipSize;
	static const float laserRateOfFire;
	static const float projectileSpawnRadius;
	static const float minimumSpawnRadius;

private:	
	bool m_enginesActive;
	bool m_moveForward;
	bool m_moveBackward;
	bool m_turnLeft;
	bool m_turnRight;
	bool m_fireLaser;

	bool m_initialLaserBeamSpawned;
	unsigned int m_fireLaserTimeElapsed;

	SpaceShipMovementDirections::SpaceShipMovementDirection m_movementDirection;
	SpaceShipColours::SpaceShipColour m_colour;

	QVector<const Sprite *> m_idleSprites;
	QVector<SpriteAnimation *> m_movementAnimations;
	
	ProjectileSystem * m_projectileSystem;
};

#endif // SPACE_SHIP_H