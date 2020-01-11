#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "SnakeGameSettings.hpp"
#include "SnakeMap.h"
#include "Snake.h"

class SnakeGame {
public:
	SnakeGame(SnakeGameSettings settings = DEFAULT_SETTINGS);
	void run();
private:
	void handleEvents();
	void render();
	sf::RenderWindow window_;

	SnakeGameSettings settings_;
	SnakeMap map_;
	Snake snake_;
};

