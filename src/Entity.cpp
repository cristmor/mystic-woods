#include "Entity.hpp"

Entity::Entity(std::string tag, size_t id, const sf::Vector2f& position, const sf::Vector2f& speed, const Animation& animation):
	mTag(tag),
	mID(id),
	mPosition(position),
	mPrevPosition(position),
	mSpeed(speed),
	mAnimation(animation){
	update();
}

// Public
void Entity::update() {
	mAnimation.update();
	mAnimation.setPosition(mPosition);
}

void Entity::setPosition(const sf::Vector2f& newPosition) {
	mPrevPosition = mPosition;
	mPosition = newPosition;
}
