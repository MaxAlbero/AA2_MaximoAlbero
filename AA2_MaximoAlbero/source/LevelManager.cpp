#include "LevelManager.h"
#include <iostream>

LevelManager::LevelManager() : currentLevel(1) {
	// Constructor vacío
}

std::string LevelManager::GetLevelPath(int levelNumber) {
	return "resources/level_" + std::to_string(levelNumber) + ".xml";
}

bool LevelManager::LoadLevelData(int levelNumber) {
	// Limpiar datos anteriores
	waveOrder.clear();
	amountEnemies.clear();

	std::string filePath = GetLevelPath(levelNumber);
	currentLevelPath = filePath;

	// Cargar el archivo XML
	if (levelLoader.LoadFile(filePath, waveOrder, amountEnemies)) {
		std::cout << "Nivel " << levelNumber << " cargado exitosamente" << std::endl;
		return true;
	}
	else {
		std::cout << "Error: No se pudo cargar el nivel " << levelNumber << std::endl;
		return false;
	}
}

bool LevelManager::InitializeLevel(int levelNumber) {
	// Validar que el nivel existe
	if (levelNumber < 1 || levelNumber > maxLevels) {
		std::cout << "Nivel " << levelNumber << " no existe. Max: " << maxLevels << std::endl;
		return false;
	}

	currentLevel = levelNumber;
	return LoadLevelData(levelNumber);
}

bool LevelManager::NextLevel() {
	if (!HasNextLevel()) {
		std::cout << "No hay más niveles. ¡Juego completado!" << std::endl;
		return false;
	}

	currentLevel++;
	return LoadLevelData(currentLevel);
}

void LevelManager::ResetCurrentLevel() {
	LoadLevelData(currentLevel);
}