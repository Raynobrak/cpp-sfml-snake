#pragma once

#include <deque>

#include <SFML/System/Vector2.hpp>

#include "SnakeMap.h"
#include "Direction.h"

class Snake {
public:
	Snake(SnakeMap& map);
	std::vector<sf::Vector2i> getBody() const;
	void move();
	void changeDirection(Direction newDir);
	bool isDead() const;
	void respawn();
	size_t length() const;
	bool occupiesPosition(sf::Vector2i pos) const;
private:
	void die();
	bool isThereSnakeBodyAt(sf::Vector2i position) const;
	sf::Vector2i direction_;
	std::deque<sf::Vector2i> snakeBody_;

	SnakeMap& map_;

	bool isDead_;
};

