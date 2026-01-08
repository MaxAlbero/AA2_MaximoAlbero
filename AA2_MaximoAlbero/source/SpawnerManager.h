#pragma once
#include "Spawner.h"
#include "Enemy.h"
#include <vector>

#define WM SpawnerManager::GetInstance()



class SpawnerManager {
public:
	static SpawnerManager* GetInstance() {
		static SpawnerManager instance;
		return &instance;
	}

	void SetEnemy(Enemy* e); //AddEnemy

	void CheckCurrentWave();

	bool GetWaveActive();
	
	bool GetNextWave();

	void SpawnPowerUp();

	void SetWaveActive(bool active);

	void SetNextWave(bool nextWave);

	void SetPositionPowerUp(Vector2 newPos);

private:
	std::vector<Enemy*> waveEnemies;
	Vector2 spawnPowerUp;
	bool _waveActive = false;
	bool _nextWave = false;
	SpawnerManager() = default;
	SpawnerManager(SpawnerManager&) = delete;
	SpawnerManager& operator= (const SpawnerManager&) = delete;
	~SpawnerManager();
};