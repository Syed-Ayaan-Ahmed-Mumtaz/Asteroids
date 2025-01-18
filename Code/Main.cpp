#include<SFML/Graphics.hpp>
#include "Game.h"
#include "Physics.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 700), "Asteroids",
		sf::Style::Close | sf::Style::Titlebar);
	sf::Clock clock;

	Game::init();

	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		sf::Event e{};
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		Game::update(window, deltaTime);
		window.display();
	}
}