#include "PowerUp.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "Player.h"
#include <iostream>

void PowerUp::OnCollision(Object* other)
{
    Player* player = dynamic_cast<Player*>(other);
    if (player != nullptr) {
        switch (lvl) {
        case 0:
            //TODO: AddScore FROM SCOREMANAGER
            break;
        case 1:
            //TODO: ADD CANNON + AMMO
            player->AddCannon();
            break;
        case 2:
            //TODO: ADD LASER + AMMO
            player->AddLaser();
            break;
        case 3:
            player->IncreaseSpeed(); //TODO: NEED TO REWORK THE SPEED POWERUP FUNCTIONALITY
            break;
        case 4:
            //TODO: ADD TWIN TURRETS
            player->AddTwinTurrets();
            break;
        case 5:
            player->RestoreFullEnergy();
            break;
        }
        //std::cout << "PowerUp recogido!" << std::endl;
        //ApplyEffect(player);
        this->Destroy();
    }
    else if (PlayerBullet* bullet = dynamic_cast<PlayerBullet*>(other)){
        bullet->Destroy();
        AddHit();
    }
}

void PowerUp::Update() {
    Object::Update();
}