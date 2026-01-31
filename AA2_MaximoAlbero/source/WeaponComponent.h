#pragma once
#include "ImageObject.h"
#include "Vector2.h"

class WeaponComponent {
protected:
    ImageObject* _visual;
    Vector2 _offset;
    bool _isEquipped;

public:
    WeaponComponent(const std::string& texturePath, Vector2 textureSize, Vector2 offset, Vector2 scale)
        : _offset(offset), _isEquipped(false) {
        _visual = new ImageObject(texturePath, Vector2(0.f, 0.f), textureSize);
        _visual->GetTransform()->scale = scale;
    }

    virtual ~WeaponComponent() {
        delete _visual;
    }

    bool IsEquipped() const { return _isEquipped; }
    void Equip() { _isEquipped = true; }

    virtual void Update(Vector2 playerPosition) {
        if (!_isEquipped) return;
        _visual->GetTransform()->position = playerPosition + _offset;
        _visual->Update();
    }

    virtual void Render() {
        if (_isEquipped) {
            _visual->Render();
        }
    }

    virtual void Shoot(Vector2 playerPosition) = 0;
    virtual bool CanShoot() const { return _isEquipped; }

    ImageObject* GetVisual() { return _visual; }
};