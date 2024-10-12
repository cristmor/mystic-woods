#pragma once

// Standard
#include <fstream>

// Deps
#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>

// Project
#include "Renderer.hpp"
#include "Physics.hpp"
#include "GameState.hpp"
#include "Entity.hpp"

struct LevelData {
	sf::Vector2f position;
	std::string tag;
	std::string animationTag;
	int layer;
};

class Game {
public:
	Game();

	void run();
private:
	void movement();
	void collision();
	void animation();
	void input();
	void state();

	std::shared_ptr<Entity> mPlayer;
	Renderer mRenderer;
};
