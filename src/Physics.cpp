#include "Physics.hpp"

namespace Physics {
sf::Vector2i GetOverlap(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2) {
	sf::Vector2f pos1 = entity1->position();
	sf::Vector2f pos2 = entity2->position();
	sf::Vector2f box1 = entity1->boundingBox();
	sf::Vector2f box2 = entity2->boundingBox();

	if(!box1.x || !box2.x) return sf::Vector2i(0, 0);

	int dx, dy, ox, oy;
	dx = std::abs(pos1.x - pos2.x);
	dy = std::abs(pos1.y - pos2.y);

	ox = (box1.x/2 + box2.x/2) - dx;
	oy = (box1.y/2 + box2.y/2) - dy;

	return sf::Vector2i(ox, oy);
}
sf::Vector2i GetPrevOverlap(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2) {
	sf::Vector2f pos1 = entity1->prevPosition();
	sf::Vector2f pos2 = entity2->prevPosition();
	sf::Vector2f box1 = entity1->boundingBox();
	sf::Vector2f box2 = entity2->boundingBox();

	if(!box1.x || !box2.x) return sf::Vector2i(0, 0);

	int dx, dy, ox, oy;
	dx = std::abs(pos1.x - pos2.x);
	dy = std::abs(pos1.y - pos2.y);

	ox = (box1.x/2 + box2.x/2) - dx;
	oy = (box1.y/2 + box2.y/2) - dy;

	return sf::Vector2i(ox, oy);
}
}
