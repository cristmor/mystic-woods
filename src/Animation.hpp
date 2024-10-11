#pragma once

// Standard
#include <SFML/System/Vector2.hpp>
#include <string>
#include <cmath>

// Deps
#include "SFML/Graphics.hpp"

const float SCALE = 3.0f;

class Animation{
public:
	Animation() {}
	Animation(std::string tag, size_t count, size_t speed, size_t size, size_t index, const sf::Vector2i& offset, const sf::Vector2f& boundingBox, const sf::Texture& texture);

	void update();

	const std::string& tag() const { return mTag; }

	short int layer = 0;

private:
	friend class Entity;

	void setTexture() { mSprite.setTextureRect(sf::IntRect(std::floor(mCurrent) * mSize, (mIndex - 1) * mSize, mSize, mSize)); }

	void setPosition(const sf::Vector2f& position) { mSprite.setPosition(position); }
	const sf::Vector2f& boundingBox() const { return mBoundingBox; }
	sf::Sprite& sprite() { return mSprite; }
	const size_t& size() const { return mSize;}

	sf::Sprite mSprite;
	std::string mTag;
	sf::Vector2i mOffset = {0,0};
	sf::Vector2f mBoundingBox = {0,0};
	size_t mCount = 0;
	size_t mCurrent = 0;
	size_t mSpeed = 0;
	size_t mIndex = 0; // Y index for texture image
	size_t mSize = 0; // In size is pixels
};
