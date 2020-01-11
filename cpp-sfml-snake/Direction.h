#pragma once

#include <array>
#include <SFML/System/Vector2.hpp>

enum class Direction {
	Up,
	Down,
	Left,
	Right,
	MAX
};

sf::Vector2i directionToUnitVector(Direction dir);