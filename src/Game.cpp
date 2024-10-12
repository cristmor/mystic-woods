#include "Game.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
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
		input();
		state();
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

	if (mPlayer->state == "right") {
		if (mPlayer->animationTag() != "player_5") {
			mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_5"));
		}
		mPlayer->sprite().setScale(SCALE, SCALE); // Reset to default scale when moving right
	}

	if (mPlayer->state == "left") {
		if (mPlayer->animationTag() != "player_5") {
			mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_5"));
		}
		mPlayer->sprite().setScale(-SCALE, SCALE); // Flip the sprite when moving left
	}

	if(mPlayer->state == "attack") {
		if(mPlayer->prevState == "down" && mPlayer->animationTag() != "player_7")
			mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_7"));

		if(mPlayer->prevState == "up" && mPlayer->animationTag() != "player_9")
			mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_9"));

		if(mPlayer->prevState == "right") {
			if (mPlayer->animationTag() != "player_8") {
				mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_8"));
			}
			mPlayer->sprite().setScale(SCALE, SCALE); // Reset to default scale when moving right
		}

		if(mPlayer->prevState == "left") {
			if (mPlayer->animationTag() != "player_8") {
				mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_8"));
			}
			mPlayer->sprite().setScale(-SCALE, SCALE); // Flip the sprite when moving left
		}
	}

	if(mPlayer->state == "idle") {
		if(mPlayer->prevState == "down" && mPlayer->animationTag() != "player_1")
			mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_1"));

		if(mPlayer->prevState == "up" && mPlayer->animationTag() != "player_3")
			mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_3"));

		if(mPlayer->prevState == "right") {
			if (mPlayer->animationTag() != "player_2") {
				mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_2"));
			}
			mPlayer->sprite().setScale(SCALE, SCALE); // Reset to default scale when moving right
		}

		if(mPlayer->prevState == "left") {
			if (mPlayer->animationTag() != "player_2") {
				mPlayer->setAnimation(GameState::getInstance().assets().getAnimation("player_2"));
			}
			mPlayer->sprite().setScale(-SCALE, SCALE); // Flip the sprite when moving left
		}
	}
}

void Game::input() {
	auto& window = GameState::getInstance().window();

	sf::Event event;
	while(window.pollEvent(event)) {
		if(event.type == sf::Event::Closed) {
			window.close();
		}

		if(event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::Space) {
				std::cout << "attack" << std::endl;
				mPlayer->input.attack = true;
			}
		}
		if(event.type == sf::Event::KeyReleased) {
			if(event.key.code == sf::Keyboard::Space) {
				mPlayer->input.attack = false;
			}
		}
	}

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

void Game::state() {
	if(mPlayer->input.left) {
		mPlayer->state = "left";
		mPlayer->prevState = "left";
	}
	else if(mPlayer->input.right) {
		mPlayer->state = "right";
		mPlayer->prevState = "right";
	}
	else if(mPlayer->input.down) {
		mPlayer->state = "down";
		mPlayer->prevState = "down";
	}
	else if(mPlayer->input.up) {
		mPlayer->state = "up";
		mPlayer->prevState = "up";
	}
	else if(mPlayer->input.attack) {
		mPlayer->state = "attack";
	}
	else {
		mPlayer->state = "idle";
	}

}
