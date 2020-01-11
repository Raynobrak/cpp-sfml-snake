#pragma once

#include <vector>
#include <string>

struct SnakeGameSettings {
	int mapWidth;
	int mapHeight;

	int snakeColorR;
	int snakeColorG;
	int snakeColorB;

	int windowWidth;
	int windowHeight;

	float timeBetweenMoves;
};

constexpr SnakeGameSettings DEFAULT_SETTINGS = { 30,20,255,0,0, 800, 500, 0.05f };

//std::vector<std::string> findErrorsInSettings(const SnakeGameSettings& settings) {
//	std::vector<std::string> errors;
//	// todo analyser la configuration et trouver les erreurs de logique (par exemple : taille de la map négative).
//	return errors;
//}