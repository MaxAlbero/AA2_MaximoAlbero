#pragma once
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include <vector>

#define ENTITY_MGR EntitiesManager::GetInstance()

class EntitiesManager {
public:
	static EntitiesManager* GetInstance() {
		static EntitiesManager instance;
		return &instance;
	}

private:
	EntitiesManager() = default;
	EntitiesManager(EntitiesManager&) = delete;
	EntitiesManager& operator=(const EntitiesManager&) = delete;

	Player* _player = nullptr;
	std::vector<Enemy*> _enemies;
	std::vector<Bullet*> _playerBullets;   
	std::vector<EnemyBullet*> _enemyBullets;
};