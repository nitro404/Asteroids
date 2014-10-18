#include "SpriteAnimationSystem/SpriteAnimation.h"

const float SpriteAnimation::minimumDuration = 1.0f / 30.0f;;

SpriteAnimation::SpriteAnimation(const char * name, const char * spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type)
	: m_type(SpriteAnimationTypes::isValid(type) ? type : SpriteAnimationTypes::defaultSpriteAnimationType)
	, m_duration(duration < minimumDuration ? minimumDuration : duration)
	, m_timeElapsed(0.0f)
	, m_frameIndex(0)
	, m_finished(false)
	, m_animation(NULL)
	, m_sprite(NULL) {
	m_animation = Animation::create();
	setName(name);
	setSpriteFileName(spriteFileName);
}

SpriteAnimation::SpriteAnimation(const char * name, const char * spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type, const std::vector<SpriteFrame *> & sprites)
	: m_type(SpriteAnimationTypes::isValid(type) ? type : SpriteAnimationTypes::defaultSpriteAnimationType)
	, m_duration(duration < minimumDuration ? minimumDuration : duration)
	, m_timeElapsed(0.0f)
	, m_frameIndex(0)
	, m_finished(false)
	, m_animation(NULL)
	, m_sprite(NULL) {
	m_animation = Animation::create();
	setName(name);
	setSpriteFileName(spriteFileName);
	addSprites(sprites);
}

SpriteAnimation::SpriteAnimation(const std::string & name, const std::string & spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type)
	: m_type(SpriteAnimationTypes::isValid(type) ? type : SpriteAnimationTypes::defaultSpriteAnimationType)
	, m_duration(duration < minimumDuration ? minimumDuration : duration)
	, m_timeElapsed(0.0f)
	, m_frameIndex(0)
	, m_finished(false)
	, m_animation(NULL)
	, m_sprite(NULL) {
	m_animation = Animation::create();
	setName(name);
	setSpriteFileName(spriteFileName);
}

SpriteAnimation::SpriteAnimation(const std::string & name, const std::string & spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type, const std::vector<SpriteFrame *> & sprites)
	: m_type(SpriteAnimationTypes::isValid(type) ? type : SpriteAnimationTypes::defaultSpriteAnimationType)
	, m_duration(duration < minimumDuration ? minimumDuration : duration)
	, m_timeElapsed(0.0f)
	, m_frameIndex(0)
	, m_finished(false)
	, m_animation(NULL)
	, m_sprite(NULL) {
	m_animation = Animation::create();
	setName(name);
	setSpriteFileName(spriteFileName);
	addSprites(sprites);
}

SpriteAnimation::~SpriteAnimation() {

}

const char * SpriteAnimation::getName() const {
	return m_name.data();
}

const char * SpriteAnimation::getSpriteFileName() const {
	return m_spriteFileName.data();
}

SpriteAnimationTypes::SpriteAnimationType SpriteAnimation::getType() const {
	return m_type;
}

const char * SpriteAnimation::getTypeName() const {
	return SpriteAnimationTypes::toString(m_type);
}

float SpriteAnimation::getDuration() const {
	return m_duration;
}

float SpriteAnimation::getTimeElapsed() const {
	return m_timeElapsed;
}

bool SpriteAnimation::isFinished() const {
	return m_finished;
}

Animation * SpriteAnimation::getAnimation() const {
	return m_animation;
}

Sprite * SpriteAnimation::getSprite() const {
	return m_sprite;
}

void SpriteAnimation::setName(const char * name) {
	if(name == NULL) {
		m_name = std::string();
	}
	else {
		m_name = Utilities::trimString(std::string(name));
	}
}

void SpriteAnimation::setName(const std::string & name) {
	m_name = Utilities::trimString(name);
}

void SpriteAnimation::setSpriteFileName(const char * spriteFileName) {
	if(spriteFileName == NULL) {
		m_spriteFileName = std::string();
	}
	else {
		m_spriteFileName = Utilities::trimString(std::string(spriteFileName));
	}
}

void SpriteAnimation::setSpriteFileName(const std::string & spriteFileName) {
	m_spriteFileName = Utilities::trimString(spriteFileName);
}

bool SpriteAnimation::setType(SpriteAnimationTypes::SpriteAnimationType type) {
	if(!SpriteAnimationTypes::isValid(type)) { return false; }

	m_type = type;

//	update(0);

	return true;
}

bool SpriteAnimation::setType(int type) {
	if(!SpriteAnimationTypes::isValid(type)) { return false; }

	m_type = static_cast<SpriteAnimationTypes::SpriteAnimationType>(type);

//	update(0);

	return true;
}

bool SpriteAnimation::setType(const char * typeName) {
	if(typeName == NULL || Utilities::stringLength(typeName) == 0) { return false; }

	SpriteAnimationTypes::SpriteAnimationType type = SpriteAnimationTypes::parseFrom(typeName);
	if(!SpriteAnimationTypes::isValid(type)) { return false; }

	m_type = type;

//	update(0);

	return true;
}

bool SpriteAnimation::setType(const std::string & typeName) {
	if(typeName.empty()) { return false; }

	SpriteAnimationTypes::SpriteAnimationType type = SpriteAnimationTypes::parseFrom(typeName);
	if(!SpriteAnimationTypes::isValid(type)) { return false; }

	m_type = type;

//	update(0);

	return true;
}

bool SpriteAnimation::setDuration(float duration) {
	if(duration < minimumDuration) { return false; }

	m_duration = duration;
	m_animation->setDelayPerUnit(m_duration / static_cast<float>(m_sprites.size()));

//	update(0);

	return true;
}

int SpriteAnimation::numberOfSprites() const {
	return static_cast<int>(m_sprites.size());
}

bool SpriteAnimation::hasSprite(const SpriteFrame * sprite) const {
	for(unsigned int i=0;i<m_sprites.size();i++) {
		if(m_sprites[i] == sprite) {
			return true;
		}
	}
	return false;
}

int SpriteAnimation::indexOfSprite(const SpriteFrame * sprite) const {
	for(unsigned int i=0;i<m_sprites.size();i++) {
		if(m_sprites[i] == sprite) {
			return i;
		}
	}
	return -1;
}

const SpriteFrame * SpriteAnimation::getSprite(int index) const {
	if(index < 0 || index >= static_cast<int>(m_sprites.size())) { return NULL; }

	return m_sprites[index];
}

bool SpriteAnimation::addSprite(SpriteFrame * sprite) {
	if(sprite == NULL) {
		return false;
	}

	m_sprites.push_back(sprite);
	m_animation->addSpriteFrame(sprite);

	if(m_sprite == NULL) {
		m_sprite = Sprite::createWithSpriteFrameName(m_spriteFileName.data());
	}

	m_animation->setDelayPerUnit(m_duration / static_cast<float>(m_sprites.size()));

//	update(0);

	return true;
}


bool SpriteAnimation::addSprites(const std::vector<SpriteFrame *> & sprites) {
	bool addedSprite = false;
	for(unsigned int i=0;i<sprites.size();i++) {
		addedSprite = addSprite(sprites[i]) || addedSprite;
	}

	return addedSprite;
}

SpriteAnimation * SpriteAnimation::readFrom(FILE * input) {
	if(input == NULL) { return NULL; }

	char buffer[256];
	std::string line;
	std::string id, value;
	std::string animationName, spriteName, spriteSheetName, spriteFileName, fileName;
	SpriteAnimationTypes::SpriteAnimationType animationType = SpriteAnimationTypes::Invalid;
	float animationDuration = -1;
	int numberOfFrames = -1;
	int frameNumber = -1;
	SpriteFrame * sprite;
	bool addAnimation = false;

	SpriteAnimation * newSpriteAnimation = NULL;
	std::vector<SpriteFrame *> animationSprites;

	while(true) {
		fgets(buffer, 256, input);

		if(feof(input)) { return NULL; }

		line = Utilities::trimString(buffer);
		if(line.length() == 0) { continue; }

		id = Utilities::getVariableID(line);
		if(id.empty()) { continue; }

		value = Utilities::getVariableValue(line);
		
		if(Utilities::compareStringsIgnoreCase(id.data(), "Animation Name") == 0) {
			animationName = value;
		}
		else if(Utilities::compareStringsIgnoreCase(id.data(), "Animation Type") == 0) {
			animationType = SpriteAnimationTypes::parseFrom(value);
			if(!SpriteAnimationTypes::isValid(animationType)) {
				return NULL;
			}
		}
		else if(Utilities::compareStringsIgnoreCase(id.data(), "Animation Duration") == 0) {
			bool valid = false;
			animationDuration = Utilities::parseFloat(value, &valid);
			if(!valid || animationDuration < minimumDuration) {
				return NULL;
			}
		}
		else if(Utilities::compareStringsIgnoreCase(id.data(), "Sprite Name") == 0) {
			spriteName = value;
		}
		else if(Utilities::compareStringsIgnoreCase(id.data(), "Sprite Sheet Name") == 0) {
			spriteSheetName = value;
		}
		else if(Utilities::compareStringsIgnoreCase(id.data(), "Number of Frames") == 0) {
			bool valid = false;
			numberOfFrames = Utilities::parseInteger(value, &valid);
			if(!valid || numberOfFrames < 1) {
				return NULL;
			}
		}

		if(!animationName.empty() &&
		   SpriteAnimationTypes::isValid(animationType) &&
		   animationDuration >= minimumDuration &&
		   numberOfFrames > 0) {
			

			if((spriteName.empty() && !spriteSheetName.empty()) || 
			   (!spriteName.empty() && spriteSheetName.empty())) {
				return NULL;
			}
			else if(spriteName.empty() && spriteSheetName.empty()) {
				for(int i=0;i<numberOfFrames;i++) {
					animationSprites.push_back(NULL);
				}

				int numberOfSprites = 0;

				while(true) {
					fgets(buffer, 256, input);

					if(feof(input)) { return NULL; }

					line = Utilities::trimString(buffer);
					if(line.length() == 0) { continue; }
					
					id = Utilities::getVariableID(line);
					if(id.empty()) { continue; }

					value = Utilities::getVariableValue(line);
					
					if(Utilities::compareStringsIgnoreCase(id.data(), "Frame") == 0) {
						bool valid = false;
						frameNumber = Utilities::parseInteger(value, &valid);
						if(frameNumber < 1 || frameNumber > numberOfFrames) {
							return NULL;
						}
					}
					else if(Utilities::compareStringsIgnoreCase(id.data(), "Sprite Name") == 0) {
						spriteName = value;
					}
					else if(Utilities::compareStringsIgnoreCase(id.data(), "Sprite Sheet Name") == 0) {
						spriteSheetName = value;
					}

					if(frameNumber > 0 && !spriteName.empty() && !spriteSheetName.empty()) {
						fileName = spriteName;
						fileName.append(".png");
						sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName.data());
						if(sprite == NULL) { return NULL; }
					
						animationSprites[frameNumber - 1] = sprite;
						if(frameNumber == 1) {
							spriteFileName = fileName;
						}

						numberOfSprites++;

						spriteName.clear();
						spriteSheetName.clear();
						frameNumber = -1;

						if(numberOfSprites >= numberOfFrames) {
							for(unsigned int i=0;i<animationSprites.size();i++) {
								if(animationSprites[i] == NULL) {
									return NULL;
								}
							}

							break;
						}
					}
				}
			}
			
			if(animationSprites.empty()) {
				std::string prefix;
				int separatorIndex = -1;
				int spriteNumber = 1;
				for(int i=spriteName.length()-1;i>=0;i--) {
					if(spriteName[i] < '0' || spriteName[i] > '9') {
						separatorIndex = i;
						break;
					}
				}
				if(separatorIndex >= 0) {
					prefix = Utilities::substring(spriteName, 0, separatorIndex);
					spriteNumber = Utilities::parseInteger(Utilities::substring(spriteName, separatorIndex + 1, spriteName.length()));
				}
				else {
					prefix = spriteName;
				}

				for(int i=0;i<numberOfFrames;i++) {
					std::stringstream fileNameStream;
					fileNameStream << prefix << " " << (spriteNumber + i) << ".png";
					fileName = fileNameStream.str();

					sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName.data());
					if(sprite == NULL) { return NULL; }

					if(i == 0) {
						spriteFileName = fileName;
					}

					if(sprite != NULL) {
						animationSprites.push_back(sprite);
					}
				}
			}

			if(animationSprites.size() != numberOfFrames) { return NULL; }

			newSpriteAnimation = new SpriteAnimation(animationName.data(), spriteFileName.data(), animationDuration, animationType);
			newSpriteAnimation->addSprites(animationSprites);

			return newSpriteAnimation;
		}
	}

	return NULL;
}

bool SpriteAnimation::operator == (const SpriteAnimation & s) const {
	if(Utilities::compareStrings(m_name, s.m_name) != 0) { return false; }

	if(m_duration != s.m_duration) { return false; }

	if(m_sprites.size() != s.m_sprites.size()) { return false; }

	for(unsigned int i=0;i<m_sprites.size();i++) {
		if(m_sprites[i] != s.m_sprites[i]) {
			return false;
		}
	}
	return true;
}

bool SpriteAnimation::operator != (const SpriteAnimation & s) const {
	return !operator == (s);
}
