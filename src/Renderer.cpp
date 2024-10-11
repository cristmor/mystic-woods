#include "Renderer.hpp"
#include "GameState.hpp"
#include <SFML/Window/Event.hpp>

// Public
void Renderer::render() {
	auto& window = GameState::getInstance().window();

	window.clear();
	for(auto& entity : GameState::getInstance().entityManager().entities()) {
		if(entity) {
			entity->update();
			window.draw(entity->sprite());
		}
	}
	window.display();

	escape();
}

// Private
void Renderer::escape() {
	auto& window = GameState::getInstance().window();

	sf::Event event;
	while(window.pollEvent(event)) {
		if(event.type == sf::Event::Closed) {
			window.close();
		}
	}
}
