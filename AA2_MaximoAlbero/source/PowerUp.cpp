#include "PowerUp.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "Player.h"
#include <iostream>

void PowerUp::OnCollision(Object* other)
{
    Player* player = dynamic_cast<Player*>(other);
    if (player != nullptr) {
        std::cout << "PowerUp recogido!" << std::endl;
        ApplyEffect(player);
        this->Destroy();
    }
}

void PowerUp::Update() {
    Object::Update();
}