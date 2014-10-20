#include "SpriteAnimationSystem/SpriteAnimation.h"

const float SpriteAnimation::minimumDuration = 1.0f / 30.0f;

SpriteAnimation::SpriteAnimation(const char * name, const char * spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type)
	: m_name(Utilities::trimString(std::string(name)))
	, m_spriteFileName(Utilities::trimString(std::string(spriteFileName)))
	, m_type(SpriteAnimationTypes::isValid(type) ? type : SpriteAnimationTypes::defaultSpriteAnimationType)
	, m_duration(duration < minimumDuration ? minimumDuration : duration)
	, m_sprite(NULL)
	, m_animation(NULL)
	, m_action(NULL)
	, m_playing(false) {
	
}

SpriteAnimation::SpriteAnimation(const char * name, const char * spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type, const std::vector<SpriteFrame *> & sprites)
	: m_name(Utilities::trimString(std::string(name)))
	, m_spriteFileName(Utilities::trimString(std::string(spriteFileName)))
	, m_type(SpriteAnimationTypes::isValid(type) ? type : SpriteAnimationTypes::defaultSpriteAnimationType)
	, m_duration(duration < minimumDuration ? minimumDuration : duration)
	, m_sprite(NULL)
	, m_animation(NULL)
	, m_action(NULL)
	, m_playing(false) {
	addSpriteFrames(sprites);
}

SpriteAnimation::SpriteAnimation(const std::string & name, const std::string & spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type)
	: m_name(Utilities::trimString(name))
	, m_spriteFileName(Utilities::trimString(spriteFileName))
	, m_type(SpriteAnimationTypes::isValid(type) ? type : SpriteAnimationTypes::defaultSpriteAnimationType)
	, m_duration(duration < minimumDuration ? minimumDuration : duration)
	, m_sprite(NULL)
	, m_animation(NULL)
	, m_action(NULL)
	, m_playing(false) {

}

SpriteAnimation::SpriteAnimation(const std::string & name, const std::string & spriteFileName, float duration, SpriteAnimationTypes::SpriteAnimationType type, const std::vector<SpriteFrame *> & sprites)
	: m_name(Utilities::trimString(name))
	, m_spriteFileName(Utilities::trimString(spriteFileName))
	, m_type(SpriteAnimationTypes::isValid(type) ? type : SpriteAnimationTypes::defaultSpriteAnimationType)
	, m_duration(duration < minimumDuration ? minimumDuration : duration)
	, m_sprite(NULL)
	, m_animation(NULL)
	, m_action(NULL)
	, m_playing(false) {
	addSpriteFrames(sprites);
}

SpriteAnimation::SpriteAnimation(const SpriteAnimation & s)
	: m_name(s.m_name)
	, m_spriteFileName(s.m_spriteFileName)
	, m_type(s.m_type)
	, m_duration(s.m_duration)
	, m_sprite(NULL)
	, m_animation(NULL)
	, m_action(NULL)
	, m_playing(false) {
	addSpriteFrames(s.m_sprites);
}

SpriteAnimation & SpriteAnimation::operator = (const SpriteAnimation & s) {
	if(m_action != NULL) { m_action->stop(); }
	m_sprites.clear();

	m_name = s.m_name;
	m_spriteFileName = s.m_spriteFileName;
	m_type = s.m_type;
	m_duration = s.m_duration;
	m_sprite = NULL;
	m_animation = NULL;
	m_action = NULL;
	m_playing = false;

	addSpriteFrames(s.m_sprites);

	return *this;
}

SpriteAnimation::~SpriteAnimation() {
	if(m_playing) {
		stop();
	}
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

	return true;
}

bool SpriteAnimation::setType(int type) {
	if(!SpriteAnimationTypes::isValid(type)) { return false; }

	m_type = static_cast<SpriteAnimationTypes::SpriteAnimationType>(type);

	return true;
}

bool SpriteAnimation::setType(const char * typeName) {
	if(typeName == NULL || Utilities::stringLength(typeName) == 0) { return false; }

	SpriteAnimationTypes::SpriteAnimationType type = SpriteAnimationTypes::parseFrom(typeName);
	if(!SpriteAnimationTypes::isValid(type)) { return false; }

	m_type = type;

	return true;
}

bool SpriteAnimation::setType(const std::string & typeName) {
	if(typeName.empty()) { return false; }

	SpriteAnimationTypes::SpriteAnimationType type = SpriteAnimationTypes::parseFrom(typeName);
	if(!SpriteAnimationTypes::isValid(type)) { return false; }

	m_type = type;

	return true;
}

bool SpriteAnimation::setDuration(float duration) {
	if(duration < minimumDuration) { return false; }

	m_duration = duration;

	return true;
}

bool SpriteAnimation::play() {
	if(m_playing) { return true; }
	if(m_sprite == NULL) { return false; }

	m_animation = Animation::create();
	for(unsigned int i=0;i<m_sprites.size();i++) {
		m_animation->addSpriteFrame(m_sprites[i]);
	}
	m_animation->setRestoreOriginalFrame(m_type == SpriteAnimationTypes::Loop);
	m_animation->setDelayPerUnit(m_duration / static_cast<float>(m_sprites.size()));

	if(m_type == SpriteAnimationTypes::Loop) {
		m_action = RepeatForever::create(Animate::create(m_animation));
	}
	else if(m_type == SpriteAnimationTypes::Single) {
		m_action = Repeat::create(Animate::create(m_animation), 1);
	}
	else {
		return false;
	}

	m_sprite->runAction(m_action);

	m_playing = true;

	return true;
}

bool SpriteAnimation::isPlaying() const {
	return m_playing;
}

bool SpriteAnimation::isFinished() const {
	if(!m_playing || m_action == NULL) { return true; }
	if(m_type == SpriteAnimationTypes::Loop) { return false; }

	return m_action->isDone();
}

void SpriteAnimation::stop() {
	if(!m_playing) { return; }

	m_action->stop();
	if(m_sprite != NULL) { m_sprite->stopAction(m_action); }
	m_animation = NULL;
	m_action = NULL;
	m_playing = false;
}

void SpriteAnimation::update(float timeElapsed) {
	if(m_playing && isFinished()) {
		m_action->stop();
		if(m_sprite != NULL) { m_sprite->stopAction(m_action); }
		m_animation = NULL;
		m_action = NULL;
		m_playing = false;
	}
}

int SpriteAnimation::numberOfSpriteFrames() const {
	return static_cast<int>(m_sprites.size());
}

bool SpriteAnimation::hasSpriteFrame(const SpriteFrame * sprite) const {
	for(unsigned int i=0;i<m_sprites.size();i++) {
		if(m_sprites[i] == sprite) {
			return true;
		}
	}
	return false;
}

int SpriteAnimation::indexOfSpriteFrame(const SpriteFrame * sprite) const {
	for(unsigned int i=0;i<m_sprites.size();i++) {
		if(m_sprites[i] == sprite) {
			return i;
		}
	}
	return -1;
}

SpriteFrame * SpriteAnimation::getSpriteFrame(int index) const {
	if(index < 0 || index >= static_cast<int>(m_sprites.size())) { return NULL; }

	return m_sprites[index];
}

bool SpriteAnimation::addSpriteFrame(SpriteFrame * sprite) {
	if(sprite == NULL) {
		return false;
	}

	m_sprites.push_back(sprite);
	
	if(m_sprite == NULL) {
		m_sprite = Sprite::createWithSpriteFrameName(m_spriteFileName.data());
	}

	return true;
}

bool SpriteAnimation::addSpriteFrames(const std::vector<SpriteFrame *> & sprites) {
	bool addedSprite = false;
	for(unsigned int i=0;i<sprites.size();i++) {
		addedSprite = addSpriteFrame(sprites[i]) || addedSprite;
	}

	return addedSprite;
}

SpriteAnimation * SpriteAnimation::readFrom(FileReader & input) {
	if(!input.isOpen()) { return NULL; }

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
		if(input.endOfFile()) { return NULL; }

		line = Utilities::trimString(input.readLine());
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
					if(input.endOfFile()) { return NULL; }

					line = Utilities::trimString(input.readLine());
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
			newSpriteAnimation->addSpriteFrames(animationSprites);

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
