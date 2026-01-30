#pragma once
#include "EnemyMovement.h"
#include "EnemyBullet.h"
#include "Spawner.h"
#include <cstdlib>
#include <ctime>

class ShootMovement : public EnemyMovement {
private:
    float _cooldown;        // Tiempo entre disparos
    int _minShots;          // Mínimo de disparos
    int _maxShots;          // Máximo de disparos
    int _totalShots;        // Disparos totales a realizar (aleatorio)
    int _shotsFired;        // Disparos realizados
    float _timer;
    float _bulletSpacing;   // Espacio vertical entre balas

public:
    ShootMovement(Transform* transform, float cooldown, int minShots, int maxShots, float bulletSpacing = 50.f)
        : EnemyMovement(transform, nullptr),
        _cooldown(cooldown),
        _minShots(minShots),
        _maxShots(maxShots),
        _shotsFired(0),
        _timer(0.f),
        _bulletSpacing(bulletSpacing) {

        // Determinar número aleatorio de disparos entre min y max
        _totalShots = _minShots + (rand() % (_maxShots - _minShots + 1));
    }

    void Update(float deltaTime) override {
        if (_finished) return;

        _timer += deltaTime;
        if (_timer >= _cooldown) {
            _timer = 0.f;

            // Disparar desde múltiples posiciones
            ShootBurst();

            _shotsFired++;

            if (_shotsFired >= _totalShots) {
                _finished = true;
            }
        }
    }

private:
    void ShootBurst() {
        // Número aleatorio de balas por ráfaga (3 a 7)
        int numBullets = 3 + (rand() % 5); // 3, 4, 5, 6, o 7 balas

        // Calcular el espacio total que ocuparán las balas
        float totalHeight = (numBullets - 1) * _bulletSpacing;

        // Posición inicial centrada en el enemigo
        float startY = _transform->position.y - (totalHeight / 2.f);

        // Disparar desde el borde izquierdo del BioTitan
        float bulletX = _transform->position.x - _transform->size.x / 2.f;

        // Crear balas distribuidas verticalmente
        for (int i = 0; i < numBullets; i++) {
            float bulletY = startY + (i * _bulletSpacing);

            Vector2 bulletPos(bulletX, bulletY);
            EnemyBullet* bullet = new EnemyBullet(bulletPos);
            SPAWNER.SpawnObject(bullet);
        }
    }
};