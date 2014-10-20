#include "Entity/Entity2D.h"

Entity2D::Entity2D(Layer * parent, Sprite * sprite, const Vec2 & position, float size, const Vec2 & scale, float rotation, const Vec2 & offset, const Vec2 & velocity)
	: Entity(parent)
	, m_sprite(NULL)
	, m_position(position)
	, m_size(size < 0.0f ? 0.0f : size)
	, m_scale(scale)
	, m_rotation(rotation)
	, m_offset(offset)
	, m_velocity(velocity)
	, m_initialPosition(position)
	, m_initialScale(scale)
	, m_initialRotation(rotation)
	, m_initialOffset(offset)
	, m_initialVelocity(velocity) {
	setSprite(sprite);
}

Entity2D::Entity2D(const Entity2D & e)
	: Entity(e)
	, m_sprite(e.m_sprite)
	, m_position(e.m_position)
	, m_size(e.m_size)
	, m_scale(e.m_scale)
	, m_rotation(e.m_rotation)
	, m_offset(e.m_offset)
	, m_velocity(e.m_velocity)
	, m_initialPosition(e.m_initialPosition)
	, m_initialScale(e.m_initialScale)
	, m_initialRotation(e.m_initialRotation)
	, m_initialOffset(e.m_initialOffset)
	, m_initialVelocity(e.m_initialVelocity) {
	setSpriteFrame(e.getSpriteFrame());
}
Entity2D & Entity2D::operator = (const Entity2D & e) {
	Entity::operator = (e);

	setSpriteFrame(e.getSpriteFrame());
	
	m_position = e.m_position;
	m_size = e.m_size;
	m_scale = e.m_scale;
	m_rotation = e.m_rotation;
	m_offset = e.m_offset;
	m_velocity = e.m_velocity;

	m_initialPosition = e.m_initialPosition;
	m_initialScale = e.m_initialScale;
	m_initialRotation = e.m_initialRotation;
	m_initialOffset = e.m_initialOffset;
	m_initialVelocity = e.m_initialVelocity;

	return *this;
}

Entity2D::~Entity2D() {

}

void Entity2D::updateInitialValues() {
	m_initialPosition = m_position;
	m_initialScale = m_scale;
	m_initialRotation = m_rotation;
	m_initialOffset = m_offset;
	m_initialVelocity = m_velocity;
}

const Vec2 & Entity2D::getPosition() const {
	return m_position;
}

float Entity2D::x() const {
	return m_position.x;
}

float Entity2D::y() const {
	return m_position.y;
}

float Entity2D::getSize() const {
	return m_size;
}

float Entity2D::getWidth() const {
	return m_sprite == NULL ? 0.0f : m_sprite->getContentSize().width;
}

float Entity2D::getHeight() const {
	return m_sprite == NULL ? 0.0f : m_sprite->getContentSize().height;
}

Vec2 Entity2D::getDimensions() const {
	Size spriteDimensions = m_sprite->getContentSize();

	return Vec2(m_sprite == NULL ? 0.0f : spriteDimensions.width, m_sprite == NULL ? 0.0f : spriteDimensions.height);
}

const Vec2 & Entity2D::getScale() const {
	return m_scale;
}

float Entity2D::getRotation() const {
	return m_rotation;
}

const Vec2 & Entity2D::getOffset() const {
	return m_offset;
}

const Vec2 & Entity2D::getVelocity() const {
	return m_velocity;
}

float Entity2D::getSpeed() const {
	return sqrt(pow(m_velocity.x, 2) + pow(m_velocity.y, 2));
}

const Vec2 & Entity2D::getInitialPosition() const {
	return m_initialPosition;
}

const Vec2 & Entity2D::getInitialScale() const {
	return m_initialScale;
}

float Entity2D::getInitialRotation() const {
	return m_initialRotation;
}

const Vec2 & Entity2D::getInitialOffset() const {
	return m_initialOffset;
}

const Vec2 & Entity2D::getInitialVelocity() const {
	return m_initialVelocity;
}

void Entity2D::setPosition(float x, float y) {
	m_position.x = x;
	m_position.y = y;

	if(m_sprite != NULL) {
		m_sprite->setPosition(x, y);
	}
}

void Entity2D::setPosition(const Vec2 & position) {
	m_position = position;

	if(m_sprite != NULL) {
		m_sprite->setPosition(position);
	}
}

void Entity2D::setSize(float size) {
	if(size < 0.0f) { return; }

	m_size = size;
}

void Entity2D::setScale(float scale) {
	m_scale.x = scale;
	m_scale.y = scale;

	if(m_sprite != NULL) {
		m_sprite->setScale(scale);
	}
}

void Entity2D::setScale(float x, float y) {
	m_scale.x = x;
	m_scale.y = y;

	if(m_sprite != NULL) {
		m_sprite->setScale(x, y);
	}
}

void Entity2D::setScale(const Vec2 & scale) {
	m_scale = scale;

	if(m_sprite != NULL) {
		m_sprite->setScale(scale.x, scale.y);
	}
}

void Entity2D::setRotation(float rotation) {
	m_rotation = rotation;

	if(m_sprite != NULL) {
		m_sprite->setRotation(rotation - 90.0f);
	}
}

void Entity2D::setOffset(float x, float y) {
	m_offset.x = x;
	m_offset.y = y;
}

void Entity2D::setOffset(const Vec2 & offset) {
	m_offset = offset;
}

void Entity2D::setVelocity(float x, float y) {
	m_velocity.x = x;
	m_velocity.y = y;
}

void Entity2D::setVelocity(const Vec2 & velocity) {
	m_velocity = velocity;
}

void Entity2D::setInitialPosition(float x, float y) {
	m_initialPosition.x = x;
	m_initialPosition.y = y;
}

void Entity2D::setInitialPosition(const Vec2 & position) {
	m_initialPosition = position;
}

void Entity2D::setInitialScale(float x, float y) {
	m_initialScale.x = x;
	m_initialScale.y = y;
}

void Entity2D::setInitialScale(const Vec2 & scale) {
	m_initialScale = scale;
}

void Entity2D::setInitialRotation(float rotation) {
	m_initialRotation = rotation;
}

void Entity2D::setInitialOffset(float x, float y) {
	m_initialOffset.x = x;
	m_initialOffset.y = y;
}

void Entity2D::setInitialOffset(const Vec2 & offset) {
	m_initialOffset = offset;
}

void Entity2D::setInitialVelocity(float x, float y) {
	m_initialVelocity.x = x;
	m_initialVelocity.y = y;
}

void Entity2D::setInitialVelocity(const Vec2 & velocity) {
	m_initialVelocity = velocity;
}

SpriteFrame * Entity2D::getSpriteFrame() const {
	return m_sprite == NULL ? NULL : m_sprite->getSpriteFrame();
}

Sprite * Entity2D::getSprite() const {
	return m_sprite;
}

void Entity2D::setSprite(Sprite * sprite) {
	if(m_sprite == sprite) { return; }

	m_lastSprite = m_sprite;

	if(m_lastSprite != NULL) {
		if(m_parent != NULL) {
			m_parent->removeChild(m_lastSprite);
		}
	}
	
	m_sprite = sprite;

	if(m_sprite != NULL) {
		if(m_parent != NULL) {
			m_parent->addChild(m_sprite);
		}

		m_sprite->setPosition(m_position);
		m_sprite->setScale(m_scale.x, m_scale.y);
		m_sprite->setRotation(m_rotation - 90.0f);
	}
}

void Entity2D::setSpriteFrame(SpriteFrame * spriteFrame) {
	if(spriteFrame == NULL) {
		setSprite(NULL);
	}
	else {
		setSprite(Sprite::createWithSpriteFrame(spriteFrame));
	}
}


bool Entity2D::checkCollision(const Entity2D & entity) const {
	return checkCollision(entity.m_position, entity.m_size);
}

bool Entity2D::checkCollision(const Vec2 & position, float size) const {
	return size > 0.0f &&
		   m_size > 0.0f &&
		   sqrt(pow(position.x - m_position.x, 2) + pow(position.y - m_position.y, 2)) <= size + m_size;
}

bool Entity2D::outOfBounds() const {
	Size visibleDimensions = Director::getInstance()->getVisibleSize();
	
	return m_position.x + m_size < 0 ||
		   m_position.y + m_size < 0 ||
		   m_position.x - m_size > visibleDimensions.width ||
		   m_position.y - m_size > visibleDimensions.height;
}

void Entity2D::reset() {
	Entity::reset();

	m_position = m_initialPosition;
	m_scale = m_initialScale;
	m_rotation = m_initialRotation;
	m_offset = m_initialOffset;
	m_velocity = m_initialVelocity;

	update(0.0f);
}

void Entity2D::update(float timeElapsed) {
	Entity::update(timeElapsed);

	if(timeElapsed > 0.0f && m_velocity.length() != 0.0f) {
		m_position += m_velocity * timeElapsed;
	}
	
	if(m_sprite != NULL) {
		m_sprite->setPosition(m_position);
		m_sprite->setScale(m_scale.x, m_scale.y);
		m_sprite->setRotation(m_rotation - 90.0f);
	}
}

bool Entity2D::operator == (const Entity2D & e) const {
	return Entity::operator == (dynamic_cast<const Entity &>(e));
}

bool Entity2D::operator != (const Entity2D & e) const {
	return !operator == (e);
}
