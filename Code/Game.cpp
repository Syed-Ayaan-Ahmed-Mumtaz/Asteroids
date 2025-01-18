#include "Game.h"
#include "Asteroid.h"
#include "Player.h"
#include<fstream>

std::vector<Entity*> Game::entities{};
std::list<std::vector<Entity*>::const_iterator> Game::toRemoveList{};
std::list<Entity*> Game::toAddList{};

sf::SoundBuffer Game::shootSoundBuffer{};
sf::Sound Game::shootSound{};

size_t Game::score{};
size_t Game::highScore;
float Game::asteroidSpawnTime{};
Game::State Game::state{}; 


sf::Font Game::font{};
sf::Text Game::scoreText{};

sf::Text Game::gameOverText{};
sf::Text Game::continueText{};

sf::Text Game::highScoreText{};
sf::Text Game::titleText{};
sf::Text Game::menuText{};
sf::Text Game::playText{};


void Game::init() {

	std::ifstream file("score.dat", std::ios::binary | std::ios::in);
	if (file.is_open()) {
		file.read(reinterpret_cast<char*>(&highScore), sizeof(size_t));
		file.close();
	}

	font.loadFromFile("font.ttf");
	scoreText.setFont(font);
	scoreText.setPosition(sf::Vector2f(40, 20));
	scoreText.setCharacterSize(48);

	gameOverText.setFont(font);
	gameOverText.setPosition(sf::Vector2f(250, 350));
	gameOverText.setCharacterSize(128);
	gameOverText.setString("Game Over!");

	continueText.setFont(font);
	continueText.setPosition(sf::Vector2f(450, 550));
	continueText.setCharacterSize(24);
	continueText.setString("Press ENTER to continue....");

	highScoreText.setFont(font);
	highScoreText.setPosition(sf::Vector2f(40, 20));
	highScoreText.setCharacterSize(48);
	highScoreText.setString("High Score: " + std::to_string(highScore));

	menuText.setFont(font);
	menuText.setPosition(sf::Vector2f(420, 600));
	menuText.setCharacterSize(24);
	menuText.setString("Press ESCAPE to exit menu....");

	titleText.setFont(font);
	titleText.setPosition(sf::Vector2f(280, 350));
	titleText.setCharacterSize(128);
	titleText.setString("Asteroids");

	playText.setFont(font);
	playText.setPosition(sf::Vector2f(450, 550));
	playText.setCharacterSize(24);
	playText.setString("Press ENTER to continue....");

	shootSoundBuffer.loadFromFile("shoot.wav");
	shootSound.setBuffer(shootSoundBuffer);

	state = MENU;


}

void Game::begin() {
	state = PLAYING;
	entities.push_back(new Player());
	asteroidSpawnTime = ASTEROID_SPAWN_TIME;
	score = 0;
}

void Game::update(sf::RenderWindow& window, float deltaTime) {

	if (state == MENU) {
		window.draw(highScoreText);
		window.draw(titleText);
		window.draw(playText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			begin();
		}
		return;
	}

	toAddList.clear();
	toRemoveList.clear();
	asteroidSpawnTime -= deltaTime;

	for (size_t i = 0; i < entities.size(); i++) {
		entities[i]->update(deltaTime);
		entities[i]->render(window);
	}

	for (auto& it : toRemoveList) {
		delete* it;
		entities.erase(it);
	}

	for (auto& ptr : toAddList) {
		entities.push_back(ptr);
	}

	if (asteroidSpawnTime <= 0.0f) {
		entities.push_back(new Asteroid());
		asteroidSpawnTime = ASTEROID_SPAWN_TIME;
	}

	scoreText.setString(std::to_string(score));
	window.draw(scoreText);

	if (state == GAME_OVER) {
		entities.clear();
		window.draw(gameOverText);
		window.draw(continueText);
		window.draw(menuText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			begin();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			state = MENU;
		}
	}
}

void Game::gameOver() {
	if (score > highScore) {
		highScore = score;
		std::ofstream file("score.dat", std::ios::binary | std::ios::out);
		if (file.is_open()) {
			file.write(reinterpret_cast<const char*>(&highScore), sizeof(size_t));
			file.close();
		}
		else {
			printf("Failed to write high score to file!\n");
		}

		highScoreText.setString("High Score: " + std::to_string(highScore));

	}
	state = GAME_OVER;
}