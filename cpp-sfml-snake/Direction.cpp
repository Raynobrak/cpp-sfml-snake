#include "Direction.h"

sf::Vector2i directionToUnitVector(Direction dir) {
	static const std::array<sf::Vector2i, static_cast<size_t>(Direction::MAX)> directions = {
		sf::Vector2i{ 0 , -1},
		sf::Vector2i{ 0 ,  1},
		sf::Vector2i{-1 ,  0},
		sf::Vector2i{ 1 ,  0}
	};

	return directions[static_cast<size_t>(dir)];
}
