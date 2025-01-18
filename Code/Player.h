#pragma once
#include "Asteroid.h"
#include "Entity.h"
#include <SFML/Audio.hpp>

constexpr float PLAYER_W = 50.0f;
constexpr float PLAYER_H = 40.0f;
constexpr float TURN_SPEED = 200.0f;
constexpr float PLAYER_SPEED = 200.0f;
constexpr float SHOOT_DELAY = 0.5f;

class Player : public Entity {
public: 
	Player();

	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;

	bool checkIntersects(Asteroid* asteroid);

private:
	sf::VertexArray array;

	float shootTimer;
};

