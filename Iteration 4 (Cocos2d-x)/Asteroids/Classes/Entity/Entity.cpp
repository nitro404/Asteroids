#include "Entity/Entity.h"

int Entity::idCounter = 1;

Entity::Entity(Layer * parent)
	: m_id(idCounter++)
	, m_parent(parent) {
	
}

Entity::Entity(const Entity & e)
	: m_id(e.m_id)
	, m_parent(e.m_parent) {
	
}

Entity & Entity::operator = (const Entity & e) {
	m_id = e.m_id;
	m_parent = e.m_parent;

	return *this;
}

Entity::~Entity() {

}

int Entity::getID() const {
	return m_id;
}

bool Entity::setID(int id) {
	if(id < 0) { return false; }

	m_id = id;

	return true;
}

Layer * Entity::getParent() const {
	return m_parent;
}

void Entity::setParent(Layer * parent) {
	m_parent = parent;
}

void Entity::reset() {

}

void Entity::update(float timeElapsed) {

}

bool Entity::operator == (const Entity & e) const {
	return m_id == e.m_id;
}

bool Entity::operator != (const Entity & e) const {
	return !operator == (e);
}
