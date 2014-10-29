#include "Entity/Entity.h"

int Entity::idCounter = 1;

Entity::Entity(Layer * parentLayer)
	: m_id(idCounter++)
	, m_parentLayer(parentLayer) {
	
}

Entity::Entity(const Entity & e)
	: m_id(e.m_id)
	, m_parentLayer(e.m_parentLayer) {
	
}

Entity & Entity::operator = (const Entity & e) {
	m_id = e.m_id;
	m_parentLayer = e.m_parentLayer;

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

Layer * Entity::getParentLayer() const {
	return m_parentLayer;
}

void Entity::setParentLayer(Layer * parentLayer) {
	m_parentLayer = parentLayer;
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
