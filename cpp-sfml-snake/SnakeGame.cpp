#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>

#include "SnakeGame.h"

SnakeGame::SnakeGame(SnakeGameSettings settings) : settings_(settings), map_(settings.mapWidth, settings.mapHeight), snake_(map_) {
	window_.create({ static_cast<unsigned int>(settings_.windowWidth),static_cast<unsigned int>(settings_.windowHeight) }, "Snake !");
}

void SnakeGame::run() {
	sf::Clock clock;
	while (window_.isOpen()) {
		handleEvents();

		if (clock.getElapsedTime().asSeconds() >= settings_.timeBetweenMoves) {
			snake_.move();
			clock.restart();
		}

		render();
	}
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
			case sf::Keyboard::Up:
				snake_.changeDirection(Direction::Up);
				break;
			case sf::Keyboard::Down:
				snake_.changeDirection(Direction::Down);
				break;
			case sf::Keyboard::Left:
				snake_.changeDirection(Direction::Left);
				break;
			case sf::Keyboard::Right:
				snake_.changeDirection(Direction::Right);
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

	auto foods = map_.getFoods();
	for (const auto& foodPos : foods) {
		sf::RectangleShape shape;
		shape.setPosition(foodPos.x * tileWidth, foodPos.y * tileHeight);
		shape.setSize({ tileWidth, tileHeight });
		shape.setFillColor(sf::Color::Red);
		window_.draw(shape);
	}

	auto snakeBody = snake_.getBody();
	for (const auto& pos : snakeBody) {
		sf::RectangleShape shape;
		shape.setPosition(pos.x * tileWidth, pos.y * tileHeight);
		shape.setSize({ tileWidth, tileHeight });
		shape.setFillColor(sf::Color::Green);
		shape.setOutlineThickness(1.f);
		shape.setOutlineColor(sf::Color::Black);
		window_.draw(shape);
	}

	window_.display();
}
