#pragma once

#include <iostream>

#include "SnakeGameSettings.hpp"

#include "SnakeGame.h"
#include "ValuesLoader.h"

const std::string SETTINGS_FILENAME = "snake.settings";

int main() {
	std::vector<ValueFormat> valuesFormats = {
		{"map_width", ValType::Integer},
		{"map_height", ValType::Integer},

		{"window_width", ValType::Integer},
		{"window_height", ValType::Integer},

		{"time_between_moves", ValType::Float},
	};
	ValuesLoader loader(valuesFormats);
	loader.loadValuesFromFile(SETTINGS_FILENAME);
	if (!loader.everythingIsFine()) {
		auto errors = loader.getErrors();
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

	settings.timeBetweenMoves = loader.getValue<float>("time_between_moves");

	if (!areSettingsValid(settings)) {
		std::cout << "The settings from the config file are incoherent." << std::endl;
		return EXIT_FAILURE;
	}

	SnakeGame snake(settings);
	snake.run();

	return EXIT_SUCCESS;
}