#include "Animation.hpp"
#include <SFML/System/Vector2.hpp>

Animation::Animation(std::string tag, size_t count, size_t speed, size_t size, size_t index, const sf::Vector2i& offset, const sf::Vector2f& boundingBox, const sf::Texture& texture):
	mTag(tag),
	mCount(count),
	mSpeed(speed),
	mSize(size),
	mIndex(index),
	mOffset(offset),
	mBoundingBox({ SCALE * boundingBox.x, SCALE * boundingBox.y }),
	mSprite(texture){

	mSprite.setOrigin((mSize/2.0) + mOffset.x, (mSize/2.0) + mOffset.y);
	mSprite.setScale(SCALE, SCALE);
	setTexture();
}

// Public
void Animation::update() {
	static size_t frames = 0;
	if(mSpeed) {
		mCurrent = (frames / (mSpeed * 6)) % mCount;
	}
	setTexture();
	frames++;
}
