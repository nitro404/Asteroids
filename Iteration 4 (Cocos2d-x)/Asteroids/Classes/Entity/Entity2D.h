#ifndef ENTITY_2D_H
#define ENTITY_2D_H

#include "Entity/Entity.h"
#include "Math/Vec2.h"

class Entity2D : public Entity {
public:
	Entity2D(Layer * parent, Sprite * sprite = NULL, const Vec2 & position = Vec2::ZERO, float size = 0.0f, const Vec2 & scale = Vec2::ONE, float rotation = 0.0f, const Vec2 & offset = Vec2::ZERO, const Vec2 & velocity = Vec2::ZERO);
	Entity2D(const Entity2D & e);
	Entity2D & operator = (const Entity2D & e);
	virtual ~Entity2D();

	virtual const Vec2 & getPosition() const;
	virtual float x() const;
	virtual float y() const;
	virtual float getSize() const;

	virtual float getWidth() const;
	virtual float getHeight() const;
	virtual Vec2 getDimensions() const;

	virtual const Vec2 & getScale() const;
	virtual float getRotation() const;
	virtual const Vec2 & getOffset() const;
	virtual const Vec2 & getVelocity() const;
	virtual float getSpeed() const;

	virtual const Vec2 & getInitialPosition() const;
	virtual const Vec2 & getInitialScale() const;
	virtual float getInitialRotation() const;
	virtual const Vec2 & getInitialOffset() const;
	virtual const Vec2 & getInitialVelocity() const;

	virtual void setPosition(float x, float y);
	virtual void setPosition(const Vec2 & position);
	virtual void setSize(float size);
	virtual void setScale(float scale);
	virtual void setScale(float x, float y);
	virtual void setScale(const Vec2 & scale);
	virtual void setRotation(float rotation);
	virtual void setOffset(float x, float y);
	virtual void setOffset(const Vec2 & offset);
	virtual void setVelocity(float x, float y);
	virtual void setVelocity(const Vec2 & velocity);

	virtual void setInitialPosition(float x, float y);
	virtual void setInitialPosition(const Vec2 & position);
	virtual void setInitialScale(float x, float y);
	virtual void setInitialScale(const Vec2 & scale);
	virtual void setInitialRotation(float rotation);
	virtual void setInitialOffset(float x, float y);
	virtual void setInitialOffset(const Vec2 & offset);
	virtual void setInitialVelocity(float x, float y);
	virtual void setInitialVelocity(const Vec2 & velocity);

	virtual SpriteFrame * getSpriteFrame() const;

	virtual Sprite * getSprite() const;
	virtual void setSprite(Sprite * sprite);
	virtual void setSpriteFrame(SpriteFrame * spriteFrame);

	virtual bool checkCollision(const Entity2D & entity) const;
	virtual bool checkCollision(const Vec2 & position, float size) const;
	virtual bool outOfBounds() const;

	virtual void reset();
	virtual void update(float timeElapsed);

	bool operator == (const Entity2D & e) const;
	bool operator != (const Entity2D & e) const;

private:
	void updateInitialValues();

protected:
	Vec2 m_position;
	float m_size;
	Vec2 m_scale;
	float m_rotation;
	Vec2 m_offset;
	Vec2 m_velocity;

	Vec2 m_initialPosition;
	Vec2 m_initialScale;
	float m_initialRotation;
	Vec2 m_initialOffset;
	Vec2 m_initialVelocity;

	Sprite * m_sprite;
	SpriteFrame * m_spriteFrame;
	Sprite * m_lastSprite;
};

#endif // ENTITY_2D_H
