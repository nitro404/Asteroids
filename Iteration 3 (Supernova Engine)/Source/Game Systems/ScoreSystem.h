#ifndef SCORE_SYSTEM_H
#define SCORE_SYSTEM_H

#include <QVector.h>
#include "Sprite Animation System/SpriteAnimationCollection.h"
#include "Entity/Entity.h"
#include "Game Objects/ScoreType.h"

class SpaceShipSystem;

class ScoreSystem : public Entity {
public:
	ScoreSystem();
	ScoreSystem(const ScoreSystem & s);
	ScoreSystem & operator = (const ScoreSystem & s);
	virtual ~ScoreSystem();

	bool init(const ResourceManager * resources, SpaceShipSystem * spaceShipSystem);

	void addScore(const SpaceShip * spaceShip, ScoreTypes::ScoreType scoreType);

	virtual void reset();
	virtual void draw();

	bool operator == (const ScoreSystem & s) const;
	bool operator != (const ScoreSystem & s) const;

private:
	bool m_initialized;

	int m_playerScores[SpaceShipColours::NumberOfColours];

	Font * m_scoreFont;

	SpaceShipSystem * m_spaceShipSystem;
};

#endif // SCORE_SYSTEM_H
