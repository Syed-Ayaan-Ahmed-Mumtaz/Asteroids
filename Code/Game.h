#pragma once

#include<SFML/Audio.hpp>
#include<unordered_map>
#include<vector>
#include<list>
#include "Entity.h"

class Game {
public:
	static void init();
	static void begin();
	static void update(sf::RenderWindow& window, float deltaTime);

	static void gameOver();

	static std::vector<Entity*> entities;
	static std::list<std::vector<Entity*>::const_iterator> toRemoveList;
	static std::list<Entity*> toAddList;


	static size_t score;

	static sf::SoundBuffer shootSoundBuffer;
	static sf::Sound shootSound;

private: 
	static float asteroidSpawnTime;
	static size_t highScore;

	static sf::Font font;
	static sf::Text scoreText;

	static sf::Text gameOverText;
	static sf::Text continueText;

	static sf::Text highScoreText;
	static sf::Text titleText;
	static sf::Text menuText;
	static sf::Text playText;
	static sf::Text quitText;
	
	static enum State { MENU, PLAYING, GAME_OVER } state ; 

};

