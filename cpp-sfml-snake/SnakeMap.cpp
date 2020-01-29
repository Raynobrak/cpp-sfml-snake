#include "SnakeMap.h"

#include "Snake.h"

#include <random>

// random number generator from Stroustrup: 
// http://www.stroustrup.com/C++11FAQ.html#std-random
int rand_int(int low, int high)
{
	static std::default_random_engine re{};
	using Dist = std::uniform_int_distribution<int>;
	static Dist uid{};
	return uid(re, Dist::param_type{ low,high });
}

SnakeMap::SnakeMap(int width, int height, int maxFood, const Snake& snake) : width_(width), height_(height), maxFood_(maxFood), snake_(snake) {
	addFood();
}

std::vector<sf::Vector2i> SnakeMap::getFoods() const
{
	return foodPositions_;
}

bool SnakeMap::isOutOfBounds(sf::Vector2i nextPosition) const {
	return	nextPosition.x >= width_ ||
			nextPosition.x < 0 ||
			nextPosition.y >= height_ ||
			nextPosition.y < 0;
}

bool SnakeMap::isThereFoodAt(sf::Vector2i position) const {
	return std::find(foodPositions_.begin(), foodPositions_.end(), position) != foodPositions_.end();
}

void SnakeMap::eatFoodAt(sf::Vector2i position) {
	foodPositions_.erase(std::find(foodPositions_.begin(), foodPositions_.end(), position));
	
	addFood();
}

sf::Vector2i SnakeMap::centerPos() const {
	return sf::Vector2i(width_ / 2, height_ / 2);
}

int SnakeMap::availableTilesCount() const
{
	return width_ * height_ - snake_.length() - foodPositions_.size();
}

void SnakeMap::addFood() {
	auto snakeBody = snake_.getBody();

	while (foodPositions_.size() < maxFood_ && availableTilesCount() > 0) {
		sf::Vector2i newPos;
		do {
			newPos = { rand_int(0, width_ - 1), rand_int(0, height_ - 1) };
		} while (snake_.occupiesPosition(newPos) || isThereFoodAt(newPos));
		foodPositions_.push_back(newPos);
	}
}