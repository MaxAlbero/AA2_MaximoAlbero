#include "Bullet.h"
#include "Enemy.h"

void Bullet::OnCollision(Object* other)
{
	//HOLAAAA
	// 
	Enemy* enemy = dynamic_cast<Enemy*>(other);
	if (enemy != nullptr)
	{
		Destroy();
	}
}