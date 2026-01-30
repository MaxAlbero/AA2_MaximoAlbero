#pragma once
#include <string>
#include <vector>
#include "LoadLevel.h"

#define LM LevelManager::GetInstance()

class LevelManager {
private:
	LevelManager();
	LevelManager(LevelManager&) = delete;
	LevelManager& operator=(const LevelManager&) = delete;

	int currentLevel = 1;
	const int maxLevels = 2;
	std::string currentLevelPath = "";

	std::vector<int> waveOrder;
	std::vector<int> amountEnemies;
	LoadLevel levelLoader;

	// Métodos privados para inicializar niveles
	std::string GetLevelPath(int levelNumber);
	bool LoadLevelData(int levelNumber);

public:
	static LevelManager& GetInstance() {
		static LevelManager instance;
		return instance;
	}

	// Getters
	int GetCurrentLevel() const { return currentLevel; }
	int GetMaxLevels() const { return maxLevels; }
	bool HasNextLevel() const { return currentLevel < maxLevels; }
	std::string GetCurrentLevelPath() const { return currentLevelPath; }

	// Acceso a datos del nivel
	const std::vector<int>& GetWaveOrder() const { return waveOrder; }
	const std::vector<int>& GetAmountEnemies() const { return amountEnemies; }

	// Cargar nivel
	bool InitializeLevel(int levelNumber);

	// Transición al siguiente nivel
	bool NextLevel();

	// Reset del nivel actual
	void ResetCurrentLevel();

	~LevelManager() = default;
};