#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>

#include "SnakeGame.h"

SnakeGame::SnakeGame(SnakeGameSettings settings) : settings_(settings), map_(settings.mapWidth, settings.mapHeight), snake_(map_) {
	window_.create({ static_cast<unsigned int>(settings_.windowWidth),static_cast<unsigned int>(settings_.windowHeight) }, "Snake !");
}

void SnakeGame::run() {
	moveClock_.restart();
	while (window_.isOpen()) {
		handleEvents();

		if (moveClock_.getElapsedTime().asSeconds() >= settings_.timeBetweenMoves) {
			snake_.move();
			moveClock_.restart();
		}

		render();
	}
}

void SnakeGame::changeSnakeDir(Direction newDir) {
	snake_.changeDirection(newDir);
	snake_.move();
	moveClock_.restart();
}

void SnakeGame::handleEvents() {
	sf::Event event;
	while (window_.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window_.close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::R:
				snake_.respawn();
				break;
			case sf::Keyboard::Up:
				changeSnakeDir(Direction::Up);
				break;
			case sf::Keyboard::Down:
				changeSnakeDir(Direction::Down);
				break;
			case sf::Keyboard::Left:
				changeSnakeDir(Direction::Left);
				break;
			case sf::Keyboard::Right:
				changeSnakeDir(Direction::Right);
				break;
			}
			break;
		}
	}
}

void SnakeGame::render() {
	window_.clear();

	const float tileWidth = static_cast<float>(settings_.windowWidth) / static_cast<float>(settings_.mapWidth);
	const float tileHeight = static_cast<float>(settings_.windowHeight) / static_cast<float>(settings_.mapHeight);

	static const sf::Color SNAKE_ALIVE_COLOR = { 20,108,156 };
	static const sf::Color SNAKE_DEAD_COLOR = { 127,39,36 };
	static const sf::Color FOOD_COLOR = { 69,186,108 };

	auto foods = map_.getFoods();
	for (const auto& foodPos : foods) {
		sf::RectangleShape shape;
		shape.setPosition(foodPos.x * tileWidth, foodPos.y * tileHeight);
		shape.setSize({ tileWidth, tileHeight });
		shape.setFillColor(FOOD_COLOR);
		window_.draw(shape);
	}

	auto snakeBody = snake_.getBody();
	for (const auto& pos : snakeBody) {
		sf::RectangleShape shape;
		shape.setPosition(pos.x * tileWidth, pos.y * tileHeight);
		shape.setSize({ tileWidth, tileHeight });
		shape.setFillColor(snake_.isDead() ? SNAKE_DEAD_COLOR : SNAKE_ALIVE_COLOR);
		//shape.setOutlineThickness(1.f);
		//shape.setOutlineColor(sf::Color::Black);
		window_.draw(shape);
	}

	window_.display();
}
