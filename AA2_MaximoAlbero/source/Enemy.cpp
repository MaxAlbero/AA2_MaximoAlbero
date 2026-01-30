#include "Enemy.h"
#include "PlayerBullet.h"
#include <math.h>

void Enemy::OnCollision(Object* other)
{
    if (PlayerBullet* bullet = dynamic_cast<PlayerBullet*>(other)) {
            ReceiveDamage(10);
        if (!bullet->IsPendingDestroy()) {
            bullet->Destroy();
        }
    }
}

void Enemy::Attack(IDamageable* other) const {
	std::cout << "Enemy attacks!" << std::endl;
}