#ifndef SPRITE_ANIMATION_COLLECTION_H
#define SPRITE_ANIMATION_COLLECTION_H

#include "Utilities/Utilities.h"
#include "IO/FileReader.h"
#include "SpriteAnimationSystem/SpriteAnimation.h"

class SpriteAnimationCollection {
public:
	SpriteAnimationCollection();
	SpriteAnimationCollection(const SpriteAnimationCollection & s);
	SpriteAnimationCollection & operator = (const SpriteAnimationCollection & s);
	virtual ~SpriteAnimationCollection();

	int numberOfAnimations() const;
	bool hasAnimation(const SpriteAnimation & animation) const;
	bool hasAnimation(const char * name) const;
	bool hasAnimation(const std::string & name) const;
	int indexOfAnimation(const SpriteAnimation & animation) const;
	int indexOfAnimation(const char * name) const;
	int indexOfAnimation(const std::string & name) const;
	const SpriteAnimation * getAnimation(int index) const;
	const SpriteAnimation * getAnimation(const char * name) const;
	const SpriteAnimation * getAnimation(const std::string & name) const;
	bool addAnimation(const SpriteAnimation * animation);
	bool removeAnimation(int index);
	bool removeAnimation(const SpriteAnimation & animation);
	bool removeAnimation(const char * name);
	bool removeAnimation(const std::string & name);
	void clearAnimations();

	static SpriteAnimationCollection * readFrom(const char * spriteAnimationDefinitionFileName);
	static SpriteAnimationCollection * readFrom(const std::string & spriteAnimationDefinitionFileName);
	static SpriteAnimationCollection * readFrom(FileReader & input);

	bool operator == (const SpriteAnimationCollection & s) const;
	bool operator != (const SpriteAnimationCollection & s) const;

public:
	static const float ANIMATION_COLLECTION_VERSION;
	static const char * ANIMATION_COLLECTION_HEADER;

private:
	std::vector<const SpriteAnimation *> m_animations;
};

#endif // SPRITE_ANIMATION_COLLECTION_H
