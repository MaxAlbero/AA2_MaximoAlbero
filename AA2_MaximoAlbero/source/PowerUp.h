#pragma once
#include "ImageObject.h"
#include "Player.h"

enum PowerUpType {
    SCORE,
    CANNON,
    LASER,
    SPEED,
    OUTRIDER,
    SHIELD
};

class PowerUp : public ImageObject {
public:
    PowerUp() 
        : ImageObject("resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f)) {

        _transform->position = Vector2(RM->WINDOW_WIDTH / 2.0f, RM->WINDOW_HEIGHT / 2.0f);
        _transform->scale = Vector2(0.5f, 0.5f);

        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        _powerUp = SCORE;
    }

    ~PowerUp() {}

    void OnCollision(Object* other) override;
    void Update() override;

private:
    PowerUpType _powerUp;

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
            //UPDATE SPRITE ACCORDING TO LEVEL
            //_renderer = renderers[++lvl];
            lvl++;
            std::cout << "PWRUP LVL: " << lvl << std::endl;

            currentHits = 0;  
        }
    }
};