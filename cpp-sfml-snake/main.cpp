#pragma once

#include <iostream>

#include "SnakeGameSettings.hpp"

#include "SnakeGame.h"
#include "ValuesLoader.h"

const std::string SETTINGS_FILENAME = "snake_settings.txt";

int main() {
	std::vector<ValFormat> valuesFormats = {
		{"map_width", ValType::Integer},
		{"map_height", ValType::Integer},

		{"window_width", ValType::Integer},
		{"window_height", ValType::Integer},

		{"max_amount_of_food", ValType::Integer},

		{"time_between_moves", ValType::Float},
	};
	ValuesLoader loader(valuesFormats, SETTINGS_FILENAME);
	if (!loader.load()) {
		const auto errors = loader.getErrorList();
		for (const auto& err : errors) {
			std::cout << err << std::endl;
		}
		return EXIT_FAILURE;
	}

	SnakeGameSettings settings;
	settings.mapWidth = loader.getValue<int>("map_width");
	settings.mapHeight = loader.getValue<int>("map_height");

	settings.windowWidth = loader.getValue<int>("window_width");
	settings.windowHeight = loader.getValue<int>("window_height");

	settings.maxFood = loader.getValue<int>("max_amount_of_food");

	settings.timeBetweenMoves = loader.getValue<float>("time_between_moves");

	if (!areSettingsValid(settings)) {
		std::cout << "The settings from the config file are incoherent." << std::endl;
		return EXIT_FAILURE;
	}

	SnakeGame snake(settings);
	snake.run();

	return EXIT_SUCCESS;
}