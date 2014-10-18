#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "Utilities/Utilities.h"
#include "SpriteAnimationSystem/SpriteAnimationType.h"

class SpriteAnimation {
public:
	SpriteAnimation(const char * name, const char * spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type);
	SpriteAnimation(const char * name, const char * spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type, const std::vector<SpriteFrame *> & sprites);
	SpriteAnimation(const std::string & name, const std::string & spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type);
	SpriteAnimation(const std::string & name, const std::string & spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type, const std::vector<SpriteFrame *> & sprites);
	virtual ~SpriteAnimation();

	const char * getName() const;
	const char * getSpriteFileName() const;
	SpriteAnimationTypes::SpriteAnimationType getType() const;
	const char * getTypeName() const;
	float getDuration() const;
	float getTimeElapsed() const;
	bool isFinished() const;
	Animation * getAnimation() const;
	Sprite * getSprite() const;

	void setName(const char * name);
	void setName(const std::string & name);
	void setSpriteFileName(const char * spriteFileName);
	void setSpriteFileName(const std::string & spriteFileName);
	bool setType(SpriteAnimationTypes::SpriteAnimationType type);
	bool setType(int type);
	bool setType(const char * typeName);
	bool setType(const std::string & typeName);
	bool setDuration(float duration);

	int numberOfSprites() const;
	bool hasSprite(const SpriteFrame * sprite) const;
	int indexOfSprite(const SpriteFrame * sprite) const;
	const SpriteFrame * getSprite(int index) const;
	bool addSprite(SpriteFrame * sprite);
	bool addSprites(const std::vector<SpriteFrame *> & sprites);

	static SpriteAnimation * readFrom(FILE * input);

	bool operator == (const SpriteAnimation & s) const;
	bool operator != (const SpriteAnimation & s) const;

public:
	static const float minimumDuration;

protected:
	std::string m_name;
	std::string m_spriteFileName;
	std::vector<SpriteFrame *> m_sprites;
	SpriteAnimationTypes::SpriteAnimationType m_type;
	float m_duration;
	float m_timeElapsed;
	int m_frameIndex;
	bool m_finished;
	Animation * m_animation;
	Sprite * m_sprite;
};

#endif // SPRITE_ANIMATION_H
