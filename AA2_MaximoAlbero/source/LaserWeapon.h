#pragma once
#include "WeaponComponent.h"
#include "PlayerBullet.h"
#include "Spawner.h"

class LaserWeapon : public WeaponComponent {
private:
    int _ammo;
    int _maxAmmo;

public:
    LaserWeapon(Vector2 offset)
        : WeaponComponent("resources/image.png", Vector2(120.f, 40.f), offset, Vector2(0.35f, 0.35f)),
        _ammo(0), _maxAmmo(10) {
    }

    void Shoot(Vector2 playerPosition) override {
        if (!CanShoot()) return;

        Vector2 weaponPos = _visual->GetTransform()->position;
        Vector2 bulletOffset = Vector2(_visual->GetTransform()->size.x * 0.5f, 0.f);
        SPAWNER.SpawnObject(new PlayerBullet(weaponPos + bulletOffset));
        _ammo--;
    }

    bool CanShoot() const override {
        return _isEquipped && _ammo > 0;
    }

    void Refill() {
        _ammo = _maxAmmo;
        std::cout << "Laser ammo refilled!" << std::endl;
    }

    int GetAmmo() const { return _ammo; }
};