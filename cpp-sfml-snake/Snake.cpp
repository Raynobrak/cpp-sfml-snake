#include "Snake.h"

Snake::Snake(SnakeMap& map) : map_(map), isDead_(false), snakeBody_() {
	direction_ = directionToUnitVector(Direction::Right);
	snakeBody_.push_back(map_.centerPos());
}

std::vector<sf::Vector2i> Snake::getBody() const {
	return { snakeBody_.begin(), snakeBody_.end() };
}

void Snake::move() {
	if (isDead_) {
		return;
	}

	sf::Vector2i nextHeadPos = snakeBody_.front() + direction_;

	// Checks if the snake collides with the body.
	// This condition evaluates to false if the next head pos collides with the *previous* position of the tail because won't be in the same place after the move.
	if (isThereSnakeBodyAt(nextHeadPos) && nextHeadPos != snakeBody_.back()) {
		die();
	}	

	if (map_.isOutOfBounds(nextHeadPos)) {
		die();
		return;
	}

	if (map_.isThereFoodAt(nextHeadPos)) {
		snakeBody_.push_front(nextHeadPos);
		map_.eatFoodAt(nextHeadPos);
	}
	else {
		snakeBody_.push_front(nextHeadPos);
		snakeBody_.pop_back();
	}
}

void Snake::changeDirection(Direction newDir) {
	direction_ = directionToUnitVector(newDir);
}

bool Snake::isDead() const {
	return isDead_;
}

void Snake::respawn() {
	isDead_ = false;
	snakeBody_.clear();
	snakeBody_.push_back(map_.centerPos());
}

size_t Snake::length() const
{
	return snakeBody_.size();
}

bool Snake::occupiesPosition(sf::Vector2i pos) const
{
	return std::find(snakeBody_.begin(), snakeBody_.end(), pos) != snakeBody_.end();
}

void Snake::die() {
	isDead_ = true;
}

bool Snake::isThereSnakeBodyAt(sf::Vector2i position) const {
	return std::find(snakeBody_.begin(), snakeBody_.end(), position) != snakeBody_.end();
}
