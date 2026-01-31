#pragma once
#include "CannonWeapon.h"
#include "LaserWeapon.h"
#include "TurretWeapon.h"
#include <vector>

class WeaponManager {
private:
    CannonWeapon* _cannon;
    LaserWeapon* _laser;
    TurretWeapon* _topTurret;
    TurretWeapon* _bottomTurret;

    Vector2 _previousPosition;

public:
    WeaponManager()
        : _cannon(nullptr), _laser(nullptr), _topTurret(nullptr), _bottomTurret(nullptr) {
        _cannon = new CannonWeapon(Vector2(20.f, -30.f));
        _laser = new LaserWeapon(Vector2(20.f, 30.f));
        _topTurret = new TurretWeapon(Vector2(0.f, -50.f), true);
        _bottomTurret = new TurretWeapon(Vector2(0.f, 50.f), false);
    }

    ~WeaponManager() {
        delete _cannon;
        delete _laser;
        delete _topTurret;
        delete _bottomTurret;
    }

    void Update(Vector2 playerPosition) {
        // Actualizar rotación de torretas
        float deltaX = playerPosition.x - _previousPosition.x;
        _topTurret->UpdateRotation(deltaX);
        _bottomTurret->UpdateRotation(deltaX);

        // Actualizar posiciones
        _cannon->Update(playerPosition);
        _laser->Update(playerPosition);
        _topTurret->Update(playerPosition);
        _bottomTurret->Update(playerPosition);

        _previousPosition = playerPosition;
    }

    void Render() {
        _cannon->Render();
        _laser->Render();
        _topTurret->Render();
        _bottomTurret->Render();
    }

    void ShootAll(Vector2 playerPosition) {

        AM->PlaySound("resources/audio/sfx/fire1.wav");
        _cannon->Shoot(playerPosition);
        _laser->Shoot(playerPosition);
        _topTurret->Shoot(playerPosition);
        _bottomTurret->Shoot(playerPosition);
    }

    // PowerUp methods
    void AddCannon() {
        if (!_cannon->IsEquipped()) {
            _cannon->Equip();
            std::cout << "Cannon equipped!" << std::endl;
        }
        else {
            _cannon->Refill();
        }
    }

    void AddLaser() {
        if (!_laser->IsEquipped()) {
            _laser->Equip();
            std::cout << "Laser equipped!" << std::endl;
        }
        else {
            _laser->Refill();
        }
    }

    void AddTurret() {
        if (!_topTurret->IsEquipped()) {
            _topTurret->Equip();
            std::cout << "Top turret equipped!" << std::endl;
        }
        else if (!_bottomTurret->IsEquipped()) {
            _bottomTurret->Equip();
            std::cout << "Bottom turret equipped!" << std::endl;
        }
        else {
            std::cout << "Already have both turrets!" << std::endl;
        }
    }

    // Getters para UI
    bool HasCannon() const { return _cannon->IsEquipped(); }
    int GetCannonAmmo() const {
        return _cannon != nullptr ? _cannon->GetAmmo() : 0;
    }
    bool HasLaser() const { return _laser->IsEquipped(); }
    int GetLaserAmmo() const {
        return _laser != nullptr ? _laser->GetAmmo() : 0;
    }
    int GetNumOfTurrets() const {
        return _bottomTurret != nullptr && _topTurret != nullptr ? 2 :
            (_bottomTurret != nullptr || _topTurret != nullptr ? 1 : 0);
    }
};