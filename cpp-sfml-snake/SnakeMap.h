#pragma once

#include <vector>
#include <deque>

#include <SFML/System/Vector2.hpp>

class Snake;

class SnakeMap {
public:
	SnakeMap(int width, int height, int maxFood, const Snake& snake);
	std::vector<sf::Vector2i> getFoods() const;

	bool isOutOfBounds(sf::Vector2i nextPosition) const;
	bool isThereFoodAt(sf::Vector2i position) const;
	void eatFoodAt(sf::Vector2i position);
	sf::Vector2i centerPos() const;
private:
	const Snake& snake_;

	int availableTilesCount() const;
	void addFood();
	std::vector<sf::Vector2i> foodPositions_;
	int width_;
	int height_;
	int maxFood_;
};

