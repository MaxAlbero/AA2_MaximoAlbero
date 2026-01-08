#include "SpawnerManager.h"

void SpawnerManager::SetEnemy(Enemy* e) {
	waveEnemies.push_back(e);
}

void SpawnerManager::CheckCurrentWave()
{
	if (_waveActive) {
		for (int i = waveEnemies.size() - 1; i >= 0; i--) {
			if (waveEnemies[i]->IsPendingDestroy()) {
				waveEnemies.erase(waveEnemies.begin() + i);
			}
		}
		//if (waveEnemies.size() == 1) {
		//	spawnPowerUp = waveEnemies[0]->GetTransform()->position;
		//}
		if (waveEnemies.empty()) {
			SpawnPowerUp();
			_waveActive = false;
		}
	}
}

bool SpawnerManager::GetWaveActive()
{
	return _waveActive;
}

bool SpawnerManager::GetNextWave()
{
	return _nextWave;
}

void SpawnerManager::SpawnPowerUp()
{
	if (spawnPowerUp.x != 0 && spawnPowerUp.y != 0) {
		//SPAWNER.SpawnObject(new PowerUp(spawnPowerUp));
		spawnPowerUp = Vector2(0.f, 0.f);
	}


}

void SpawnerManager::SetWaveActive(bool active)
{
	_waveActive = active;
}

void SpawnerManager::SetNextWave(bool nextWave)
{
	_nextWave = nextWave;
}

void SpawnerManager::SetPositionPowerUp(Vector2 newPos)
{
	spawnPowerUp = newPos;
}

SpawnerManager::~SpawnerManager()
{
	for (int i = waveEnemies.size() - 1; i >= 0; i--)
	{
		if (waveEnemies[i]->IsPendingDestroy()) {
			waveEnemies.erase(waveEnemies.begin() + i);
		}
		waveEnemies.clear();
	}
}