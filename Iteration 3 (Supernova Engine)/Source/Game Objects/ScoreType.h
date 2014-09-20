#ifndef SCORE_TYPE_H
#define SCORE_TYPE_H

#include <QString.h>
#include "Utilities/Utilities.h"

namespace ScoreTypes {
	enum ScoreType {
		Invalid = -1,
		SpaceShip,
		SmallAsteroid,
		LargeAsteroid,
		NumberOfTypes
	};
	
	extern const char * typeStrings[];
	extern const int scoreValues[];
	extern const ScoreType defaultType;
	
	bool isValid(ScoreType type);
	bool isValid(int type);
	const char * toString(ScoreType type);
	const char * toString(int type);
	int getScoreValue(ScoreType type);
	int getScoreValue(int type);
	int getScoreValue(const char * data);
	int getScoreValue(const QString & data);
	ScoreType parseFrom(const char * data);
	ScoreType parseFrom(const QString & data);
}

#endif // SCORE_TYPE_H
