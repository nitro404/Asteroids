#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "Utilities/Utilities.h"
#include "IO/FileReader.h"
#include "SpriteAnimationSystem/SpriteAnimationType.h"

class SpriteAnimation {
public:
	SpriteAnimation(const char * name, const char * spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type);
	SpriteAnimation(const char * name, const char * spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type, const std::vector<SpriteFrame *> & sprites);
	SpriteAnimation(const std::string & name, const std::string & spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type);
	SpriteAnimation(const std::string & name, const std::string & spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type, const std::vector<SpriteFrame *> & sprites);
	SpriteAnimation(const SpriteAnimation & s);
	SpriteAnimation & operator = (const SpriteAnimation & s);
	virtual ~SpriteAnimation();

	const char * getName() const;
	const char * getSpriteFileName() const;
	SpriteAnimationTypes::SpriteAnimationType getType() const;
	const char * getTypeName() const;
	float getDuration() const;
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

	virtual bool play();
	virtual bool isPlaying() const;
	virtual bool isFinished() const;
	virtual void stop();
	virtual void update(float timeElapsed);

	int numberOfSpriteFrames() const;
	bool hasSpriteFrame(const SpriteFrame * sprite) const;
	int indexOfSpriteFrame(const SpriteFrame * sprite) const;
	SpriteFrame * getSpriteFrame(int index) const;
	bool addSpriteFrame(SpriteFrame * sprite);
	bool addSpriteFrames(const std::vector<SpriteFrame *> & sprites);

	static SpriteAnimation * readFrom(FileReader & input);

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
	Animation * m_animation;
	Sprite * m_sprite;
	Action * m_action;
	bool m_playing;
	Layer * m_parent;
};

#endif // SPRITE_ANIMATION_H
