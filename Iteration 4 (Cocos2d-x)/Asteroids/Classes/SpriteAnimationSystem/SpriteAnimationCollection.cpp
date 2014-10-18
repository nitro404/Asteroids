#include "SpriteAnimationSystem/SpriteAnimationCollection.h"

const float SpriteAnimationCollection::ANIMATION_COLLECTION_VERSION = 2.0;
const char * SpriteAnimationCollection::ANIMATION_COLLECTION_HEADER = "Animation Collection Definition File";

SpriteAnimationCollection::SpriteAnimationCollection() {

}

SpriteAnimationCollection::SpriteAnimationCollection(const SpriteAnimationCollection & s) {
	for(unsigned int i=0;i<s.m_animations.size();i++) {
		m_animations.push_back(new SpriteAnimation(*s.m_animations[i]));
	}
}

SpriteAnimationCollection & SpriteAnimationCollection::operator = (const SpriteAnimationCollection & s) {
	for(unsigned int i=0;i<m_animations.size();i++) {
		delete m_animations[i];
	}
	m_animations.clear();

	for(unsigned int i=0;i<s.m_animations.size();i++) {
		m_animations.push_back(new SpriteAnimation(*s.m_animations[i]));
	}

	return *this;
}

SpriteAnimationCollection::~SpriteAnimationCollection() {
	for(unsigned int i=0;i<m_animations.size();i++) {
		delete m_animations[i];
	}
}

int SpriteAnimationCollection::numberOfAnimations() const {
	return m_animations.size();
}

bool SpriteAnimationCollection::hasAnimation(const SpriteAnimation & animation) const {
	for(unsigned int i=0;i<m_animations.size();i++) {
		if(*m_animations[i] == animation) {
			return true;
		}
	}
	return false;
}

bool SpriteAnimationCollection::hasAnimation(const char * name) const {
	if(name == NULL || Utilities::stringLength(name) == 0) { return false; }

	for(unsigned int i=0;i<m_animations.size();i++) {
		if(Utilities::compareStringsIgnoreCase(m_animations[i]->getName(), name) == 0) {
			return true;
		}
	}
	return false;
}

bool SpriteAnimationCollection::hasAnimation(const std::string & name) const {
	if(name.empty()) { return false; }

	for(unsigned int i=0;i<m_animations.size();i++) {
		if(Utilities::compareStringsIgnoreCase(m_animations[i]->getName(), name.data()) == 0) {
			return true;
		}
	}
	return false;
}

int SpriteAnimationCollection::indexOfAnimation(const SpriteAnimation & animation) const {
	for(unsigned int i=0;i<m_animations.size();i++) {
		if(*m_animations[i] == animation) {
			return i;
		}
	}
	return -1;
}

int SpriteAnimationCollection::indexOfAnimation(const char * name) const {
	if(name == NULL || Utilities::stringLength(name) == 0) { return -1; }

	for(unsigned int i=0;i<m_animations.size();i++) {
		if(Utilities::compareStringsIgnoreCase(m_animations[i]->getName(), name) == 0) {
			return i;
		}
	}
	return -1;
}

int SpriteAnimationCollection::indexOfAnimation(const std::string & name) const {
	if(name.empty()) { return -1; }

	for(unsigned int i=0;i<m_animations.size();i++) {
		if(Utilities::compareStringsIgnoreCase(m_animations[i]->getName(), name.data()) == 0) {
			return i;
		}
	}
	return -1;
}

const SpriteAnimation * SpriteAnimationCollection::getAnimation(int index) const {
	if(index < 0 || index >= static_cast<int>(m_animations.size())) { return NULL; }

	return m_animations[index];
}

const SpriteAnimation * SpriteAnimationCollection::getAnimation(const char * name) const {
	if(name == NULL || Utilities::stringLength(name) == 0) { return NULL; }

	for(unsigned int i=0;i<m_animations.size();i++) {
		if(Utilities::compareStringsIgnoreCase(m_animations[i]->getName(), name) == 0) {
			return m_animations[i];
		}
	}
	return NULL;
}

const SpriteAnimation * SpriteAnimationCollection::getAnimation(const std::string & name) const {
	if(name.empty()) { return NULL; }

	for(unsigned int i=0;i<m_animations.size();i++) {
		if(Utilities::compareStringsIgnoreCase(m_animations[i]->getName(), name.data()) == 0) {
			return m_animations[i];
		}
	}
	return NULL;
}

bool SpriteAnimationCollection::addAnimation(SpriteAnimation * animation) {
	if(animation == NULL ||
	   !SpriteAnimationTypes::isValid(animation->getType()) ||
	   !SpriteAnimationTypes::isValid(animation->getType()) ||
	   animation->numberOfSprites() == 0) {
		return false;
	}
	
	m_animations.push_back(animation);

	return true;
}

bool SpriteAnimationCollection::removeAnimation(int index) {
	if(index < 0 || index >= static_cast<int>(m_animations.size())) { return false; }
	
	delete m_animations[index];
	m_animations.erase(m_animations.begin() + index);
	
	return true;
}

bool SpriteAnimationCollection::removeAnimation(const SpriteAnimation & animation) {
	for(unsigned int i=0;i<m_animations.size();i++) {
		if(*m_animations[i] == animation) {
			delete m_animations[i];
			m_animations.erase(m_animations.begin() + i);
			
			return true;
		}
	}
	return false;
}

bool SpriteAnimationCollection::removeAnimation(const char * name) {
	if(name == NULL || Utilities::stringLength(name) == 0) { return false; }

	for(unsigned int i=0;i<m_animations.size();i++) {
		if(Utilities::compareStringsIgnoreCase(m_animations[i]->getName(), name) == 0) {
			delete m_animations[i];
			m_animations.erase(m_animations.begin() + i);

			return true;
		}
	}
	return false;
}

bool SpriteAnimationCollection::removeAnimation(const std::string & name) {
	if(name.empty()) { return false; }

	for(unsigned int i=0;i<m_animations.size();i++) {
		if(Utilities::compareStringsIgnoreCase(m_animations[i]->getName(), name.data()) == 0) {
			delete m_animations[i];
			m_animations.erase(m_animations.begin() + i);

			return true;
		}
	}
	return false;
}

void SpriteAnimationCollection::clearAnimations() {
	for(unsigned int i=0;i<m_animations.size();i++) {
		delete m_animations[i];
	}
	m_animations.clear();
}

SpriteAnimationCollection * SpriteAnimationCollection::readFrom(const char * spriteAnimationDefinitionFileName) {
	if(spriteAnimationDefinitionFileName == NULL || Utilities::stringLength(spriteAnimationDefinitionFileName) == 0) { return NULL; }
	
	SpriteAnimationCollection * newSpriteAnimationCollection = NULL;

	FILE * input = fopen(spriteAnimationDefinitionFileName, "r");
	if(input == NULL) { return NULL; }
	
	newSpriteAnimationCollection = readFrom(input);
		
	fclose(input);
	
	return newSpriteAnimationCollection;
}

SpriteAnimationCollection * SpriteAnimationCollection::readFrom(FILE * input) {
	if(input == NULL) { return NULL; }

	char buffer[256];
	std::string line;
	const char * data = NULL;
	bool valid = false;
	SpriteAnimation * newSpriteAnimation = NULL;
	SpriteAnimationCollection * newSpriteAnimationCollection = NULL;
	
	bool headerMatched = false;
	
	while(true) {
		fgets(buffer, 256, input);

		if(feof(input)) { return NULL; }

		line = Utilities::trimString(buffer);
		if(line.length() == 0) { continue; }
		
		std::string headerData[2];
		int separatorIndex = -1;
		for(int i=line.length()-1;i>=0;i--) {
			if(line[i] == ' ' || line[i] == '\t') {
				separatorIndex = i;
				break;
			}
		}
		if(separatorIndex < 0) {
			headerMatched = false;
			break;
		}
		headerData[0] = Utilities::trimString(Utilities::substring(line, 0, separatorIndex));
		headerData[1] = Utilities::trimString(Utilities::substring(line, separatorIndex + 1, line.length()));
		
		if(Utilities::compareStrings(headerData[0].data(), ANIMATION_COLLECTION_HEADER) != 0) {
			headerMatched = false;
			break;
		}
		
		float version = -1;
		version = Utilities::parseFloat(headerData[1], &valid);
		if(!valid || ANIMATION_COLLECTION_VERSION != version) { return NULL; }
		
		headerMatched = true;
		
		break;
	}

	if(!headerMatched) { return NULL; }
	
	newSpriteAnimationCollection = new SpriteAnimationCollection();
	
	while(true) {
		newSpriteAnimation = SpriteAnimation::readFrom(input);
		
		if(newSpriteAnimation == NULL) { break; }
		
		newSpriteAnimationCollection->addAnimation(newSpriteAnimation);
	}
	
	return newSpriteAnimationCollection;
}

bool SpriteAnimationCollection::operator == (const SpriteAnimationCollection & s) const {
	if(m_animations.size() != s.m_animations.size()) { return false; }

	for(unsigned int i=0;i<s.m_animations.size();i++) {
		if(!hasAnimation(*s.m_animations[i])) {
			return false;
		}
	}
	return true;
}

bool SpriteAnimationCollection::operator != (const SpriteAnimationCollection & s) const {
	return !operator == (s);
}
