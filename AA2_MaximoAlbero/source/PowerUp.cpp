#include "PowerUp.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "Player.h"
#include "ScoreManager.h"
#include <iostream>
#include "AudioManager.h"

void PowerUp::OnCollision(Object* other)
{
    Player* player = dynamic_cast<Player*>(other);
    if (player != nullptr) {
        switch (lvl) {
        case 0:
            HSM->AddPoints(1000);
            break;
        case 1:
            player->AddCannon();
            break;
        case 2:
            player->AddLaser();
            break;
        case 3:
            player->IncreaseSpeed();
            break;
        case 4:
            player->AddTwinTurrets();
            break;
        case 5:
            player->RestoreFullEnergy();
            break;
        }

        this->Destroy();

        AM->PlaySound("resources/audio/sfx/pickup_battery.wav");
    }
    else if (PlayerBullet* bullet = dynamic_cast<PlayerBullet*>(other)){
        bullet->Destroy();
        AddHit();
    }
}

void PowerUp::Update() {
    Object::Update();
}