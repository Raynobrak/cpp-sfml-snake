#pragma once

#include <vector>

#include <SFML/System/Vector2.hpp>

class SnakeMap {
public:
	SnakeMap(int width, int height);
	std::vector<sf::Vector2i> getFoods() const;

	bool isOutOfBounds(sf::Vector2i nextPosition) const;
	bool isThereFoodAt(sf::Vector2i position) const;
	void eatFoodAt(sf::Vector2i position);
private:
	void spawnNewFood();
	std::vector<sf::Vector2i> foodPositions_;
	int width_;
	int height_;
};

