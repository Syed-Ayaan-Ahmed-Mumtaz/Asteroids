#include "Asteroid.h"
#include "Global.h"
#include <random>

Asteroid::Asteroid(sf::Vector2f direction, sf::Vector2f position)
	: Entity(sf::Vector2f(900, 300), 0), direction(direction), array(sf::LinesStrip, 12), life() {
	array[0].position = sf::Vector2f(-40, 40);
	array[1].position = sf::Vector2f(-50, 10);
	array[2].position = sf::Vector2f(-10, -20);
	array[3].position = sf::Vector2f(-20, -40);
	array[4].position = sf::Vector2f(10, -40);
	array[5].position = sf::Vector2f(40, -20);
	array[6].position = sf::Vector2f(40, -10);
	array[7].position = sf::Vector2f(10, 0);
	array[8].position = sf::Vector2f(40, 20);
	array[9].position = sf::Vector2f(20, 40);
	array[10].position = sf::Vector2f(0, 30);
	array[11].position = array[0].position;

	for (size_t i = 0; i < array.getVertexCount(); i++) {
		array[i].color = sf::Color::White;
	}
}

void Asteroid::update(float deltaTime) {
	life += deltaTime;

	position += ASTEROID_SPEED * direction * deltaTime;
	angle += ASTEROID_SPIN * deltaTime;

	if (position.x < ASTEROID_W / 2.0f) {
		direction.x = abs(direction.x);
	}
	else if (position.x > SCREEN_WIDTH - ASTEROID_W / 2.0f) {
		direction.x = -abs(direction.x);
	}

	if (position.y < ASTEROID_H / 2.0f) {
		direction.y = abs(direction.y);
	}
	else if (position.y > SCREEN_HEIGHT - ASTEROID_H / 2.0f) {
		direction.y = -abs(direction.y);
	}
}

void Asteroid::render(sf::RenderWindow& window) {
	window.draw(array, sf::Transform().translate(position).rotate(angle));
}

const sf::VertexArray& Asteroid::getVertexArray() const {
	return array;
}

sf::Vector2f Asteroid::getRandomDirection() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0f, 2.0f * M_PI);

	float angle = dist(gen);
	return sf::Vector2f(cos(angle), sin(angle));
}

sf::Vector2f Asteroid::getRandomPosition() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> xAxis(ASTEROID_W / 2.0f,
		SCREEN_WIDTH - ASTEROID_W / 2.0f);
	std::uniform_real_distribution<float> yAxis(ASTEROID_H / 2.0f,
		SCREEN_HEIGHT - ASTEROID_H / 2.0f);

	return sf::Vector2f(xAxis(gen), yAxis(gen));
}
