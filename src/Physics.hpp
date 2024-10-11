#pragma once

// Standard
#include <memory>

// Deps
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

// Project
#include "Entity.hpp"

namespace Physics {
	sf::Vector2i GetOverlap(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2);
	sf::Vector2i GetPrevOverlap(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2);
}
