#include "SnakeMap.h"

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

SnakeMap::SnakeMap(int width, int height) : width_(width), height_(height) {
	spawnNewFood();
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
	
	if (foodPositions_.empty()) {
		spawnNewFood();
	}
}

void SnakeMap::spawnNewFood() {
	for (int i = 0; i < 10; ++i) {
		sf::Vector2i randomPosition;
		do {
			randomPosition = { rand_int(0, width_ - 1), rand_int(0, height_ - 1) };

		} while (isThereFoodAt(randomPosition));


		foodPositions_.push_back(randomPosition);
	}
	
}


