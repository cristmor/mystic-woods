#include "Game.hpp"

#include <SFML/System/Vector2.hpp>
#include <iostream>

Game::Game() {
	GameState::getInstance();

	std::ifstream file("/home/cristmor/dev/cpp/GLGame/level.txt");

	LevelData l;

	while(file.good()) {
		file >> l.position.x
			>> l.position.y
			>> l.tag
			>> l.animationTag
			>> l.layer;

		GameState::getInstance().entityManager().addEntity(l.tag, l.position, {5, 5}, GameState::getInstance().assets().getAnimation(l.animationTag));
	}

	file.close();

	mPlayer = GameState::getInstance().entityManager().getEntity(97);
}

// Public
void Game::run() {
	while(GameState::getInstance().window().isOpen()) {
		inputs();
		movement();
		collision();
		animation();
		mRenderer.render();
	}
}

// Private
void Game::movement() {
	sf::Vector2f position = mPlayer->position();

	int incX = (mPlayer->input.right - mPlayer->input.left) * 
			((mPlayer->input.up || mPlayer->input.down) ? 0.7071 : 1) * 
			mPlayer->speed().x;
	int incY = (mPlayer->input.down - mPlayer->input.up) *
			((mPlayer->input.right || mPlayer->input.left) ? 0.7071 : 1) * 
			mPlayer->speed().y;

	if(incX < 0) {
		mPlayer->state = "left";
	}
	if(incX > 0) {
		mPlayer->state = "right";
	}
	if(incY > 0) {
		mPlayer->state = "down";
	}
	if(incY < 0) {
		mPlayer->state = "up";
	}
	if(incX == 0 && incY == 0) {
		mPlayer->state = "idle";
	}

	position.x += incX;
	position.y += incY;

	mPlayer->setPosition(position);
}
void Game::collision() {
	EntityVector entities = GameState::getInstance().entityManager().entities();

	for(std::shared_ptr<Entity> entity : entities) {
		if(entity == mPlayer || entity->boundingBox().x <= 0 || entity->boundingBox().y <= 0) {
			continue;
		}

		sf::Vector2i overlap = Physics::GetOverlap(entity, mPlayer);
		sf::Vector2i prevOverlap = Physics::GetPrevOverlap(entity, mPlayer);

		if(overlap.x > 0 && overlap.y > 0) {

			sf::Vector2f position = mPlayer->position();

			if (prevOverlap.y > prevOverlap.x) {  // Prioritize vertical adjustment
				if (mPlayer->prevPosition().x < entity->prevPosition().x) {
					position.x -= overlap.x;
				} else if (mPlayer->prevPosition().x > entity->prevPosition().x) {
					position.x += overlap.x;
				}
			} else {  // Prioritize horizontal adjustment
				if (mPlayer->prevPosition().y < entity->prevPosition().y) {
					position.y -= overlap.y;
				} else if (mPlayer->prevPosition().y > entity->prevPosition().y) {
					position.y += overlap.y;
				}
			}

			mPlayer->setPosition(position);
		}
	}
}

void Game::animation() {
	if(mPlayer->state == "down" && mPlayer->animationTag() != "player_4")
		mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_4"));

	if(mPlayer->state == "up" && mPlayer->animationTag() != "player_6")
		mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_6"));

	if(mPlayer->state == "right" && mPlayer->animationTag() != "player_5")
		mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_5"));

	if(mPlayer->state == "left" && mPlayer->animationTag() != "player_5") {
		mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_5"));
		mPlayer->sprite().setScale(-SCALE, SCALE);
	}

	if(mPlayer->state == "idle" && mPlayer->animationTag() != "player_1")
		mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_1"));
}

void Game::inputs() {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		mPlayer->input.up = true;
	}
	else {
		mPlayer->input.up = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		mPlayer->input.down = true;
	}
	else {
		mPlayer->input.down = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		mPlayer->input.right = true;
	}
	else {
		mPlayer->input.right = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		mPlayer->input.left = true;
	}
	else {
		mPlayer->input.left = false;
	}
}
