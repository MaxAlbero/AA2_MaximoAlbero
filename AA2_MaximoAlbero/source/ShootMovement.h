#pragma once
#include "EnemyMovement.h"
#include "EnemyBullet.h"
#include "Spawner.h"
#include <cstdlib>
#include <ctime>

class ShootMovement : public EnemyMovement {
private:
    float _cooldown;        
    int _minShots;          
    int _maxShots;          
    int _totalShots;        
    int _shotsFired;        
    float _timer;
    float _bulletSpacing;   

public:
    ShootMovement(Transform* transform, float cooldown, int minShots, int maxShots, float bulletSpacing = 50.f)
        : EnemyMovement(transform, nullptr),
        _cooldown(cooldown),
        _minShots(minShots),
        _maxShots(maxShots),
        _shotsFired(0),
        _timer(0.f),
        _bulletSpacing(bulletSpacing) {

        _totalShots = _minShots + (rand() % (_maxShots - _minShots + 1));
    }

    void Update(float deltaTime) override {
        if (_finished) return;

        _timer += deltaTime;
        if (_timer >= _cooldown) {
            _timer = 0.f;

            ShootBurst();

            _shotsFired++;

            if (_shotsFired >= _totalShots) {
                _finished = true;
            }
        }
    }

private:
    void ShootBurst() {
        int numBullets = 3 + (rand() % 5);

        float totalHeight = (numBullets - 1) * _bulletSpacing;

        float startY = _transform->position.y - (totalHeight / 2.f);

        float bulletX = _transform->position.x - _transform->size.x / 2.f;

        for (int i = 0; i < numBullets; i++) {
            float bulletY = startY + (i * _bulletSpacing);

            Vector2 bulletPos(bulletX, bulletY);
            EnemyBullet* bullet = new EnemyBullet(bulletPos);
            SPAWNER.SpawnObject(bullet);
        }
    }
};