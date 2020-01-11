#pragma once

#include <vector>
#include <string>

struct SnakeGameSettings {
	int mapWidth;
	int mapHeight;

	int windowWidth;
	int windowHeight;

	float timeBetweenMoves;
};

constexpr SnakeGameSettings DEFAULT_SETTINGS = { 30, 20, 800, 500, 0.05f };

inline bool areSettingsValid(const SnakeGameSettings& settings) {
	// todo analyser la configuration et trouver les erreurs de logique (par exemple : taille de la map négative).
	return true;
}