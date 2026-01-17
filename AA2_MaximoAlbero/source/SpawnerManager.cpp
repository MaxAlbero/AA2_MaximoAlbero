#include "SpawnerManager.h"
#include "PowerUp.h"

void SpawnerManager::SetEnemy(Enemy* e) {
	waveEnemies.push_back(e);
}

void SpawnerManager::CheckCurrentWave()
{
    if (_waveActive) {
        // Guardar posición del único enemigo restante
        if (waveEnemies.size() == 1) {
            spawnPowerUp = waveEnemies[0]->GetTransform()->position;
        }
        
        // Buscar enemigos destruidos
        for (int i = waveEnemies.size() - 1; i >= 0; i--) {
            if (waveEnemies[i]->IsPendingDestroy()) {
                // Guardar posición del enemigo que está a punto de morir
                Vector2 deathPosition = waveEnemies[i]->GetTransform()->position;
                
                waveEnemies.erase(waveEnemies.begin() + i);
                
                // Si después de eliminar no quedan enemigos, spawnear powerUp
                if (waveEnemies.empty()) {
                    // Usar la posición del enemigo que acaba de morir
                    spawnPowerUp = deathPosition;
                    SpawnPowerUp();
                    _waveActive = false;
                }
            }
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
        PowerUp* powerUp = new PowerUp();
        powerUp->GetTransform()->position = spawnPowerUp;
        SPAWNER.SpawnObject(powerUp);

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
    waveEnemies.clear();
}