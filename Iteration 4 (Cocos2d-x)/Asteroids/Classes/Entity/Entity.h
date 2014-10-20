#ifndef ENTITY_H
#define ENTITY_H

#include "Utilities/Utilities.h"
#include "Math/ExtendedMath.h"

class Entity {
public:
	Entity(Layer * parent);
	Entity(const Entity & e);
	Entity & operator = (const Entity & e);
	virtual ~Entity();

	int getID() const;
	bool setID(int id);

	virtual Layer * getParent() const;
	virtual void setParent(Layer * parent);

	virtual void reset();
	virtual void update(float timeElapsed);

	bool operator == (const Entity & e) const;
	bool operator != (const Entity & e) const;

protected:
	int m_id;
	Layer * m_parent;

private:
	static int idCounter;
};

#endif // ENTITY_H
