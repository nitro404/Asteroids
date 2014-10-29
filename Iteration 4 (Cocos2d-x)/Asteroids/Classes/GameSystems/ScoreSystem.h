#ifndef SCORE_SYSTEM_H
#define SCORE_SYSTEM_H

#include "SpriteAnimationSystem/SpriteAnimationCollection.h"
#include "Entity/Entity.h"
#include "GameObjects/ScoreType.h"

class SpaceShipSystem;

class ScoreSystem : public Entity, public Component {
public:
	ScoreSystem(Layer * parentLayer);
	ScoreSystem(const ScoreSystem & s);
	ScoreSystem & operator = (const ScoreSystem & s);
	virtual ~ScoreSystem();

	virtual Layer * getParentLayer() const;
	virtual void setParentLayer(Layer * parentLayer);

	bool init(SpaceShipSystem * spaceShipSystem);

	void addScore(const SpaceShip * spaceShip, ScoreTypes::ScoreType scoreType);

	virtual void reset();

	bool operator == (const ScoreSystem & s) const;
	bool operator != (const ScoreSystem & s) const;

public:
	static const char * scoreSystemClassName;

private:
	bool m_initialized;

	int m_playerScores[SpaceShipColours::NumberOfColours];

//	Font * m_scoreFont;

	SpaceShipSystem * m_spaceShipSystem;
};

#endif // SCORE_SYSTEM_H
