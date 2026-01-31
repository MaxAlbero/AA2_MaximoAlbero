#pragma once
#include "ImageObject.h"
#include "Player.h"

class PowerUp : public ImageObject {
public:
    PowerUp()
        : PowerUp(Vector2(0.f, 0.f)) {
    }

    PowerUp(Vector2 position)
        : ImageObject("resources/powerup_spritesheet.png", Vector2(0.f, 0.f), Vector2(222, 111.f)) {

        for (int i = 0; i < maxLevel; i++) {
            renderers.push_back(new ImageRenderer(
                this->_transform,
                "resources/powerup_spritesheet.png",
                Vector2(222.f * i, 0.f),
                Vector2(222.f, 111.f)
            ));
        }
        delete _renderer;
        _renderer = renderers[lvl];

        _transform->scale = Vector2(0.5f, 0.5f);
        _physics->AddCollider(new AABB(_transform->position, _transform->size));
    }

    ~PowerUp() {
        for (Renderer* r : renderers)
            delete r;
    }

    void OnCollision(Object* other) override;
    void Update() override;

private:

    int lvl = 0;
    const int maxLevel = 5;
    int currentHits = 0;
    const int maxHits = 6;

    std::vector<Renderer*> renderers;

    void AddHit() {
        if (lvl == maxLevel)
            return;

        currentHits++;
        if (currentHits == maxHits) {
            _renderer = renderers[++lvl];

            currentHits = 0;
        }
    }
};