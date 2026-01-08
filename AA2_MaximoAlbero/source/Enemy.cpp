#include "Enemy.h"
#include "Bullet.h"
#include <math.h>

void Enemy::OnCollision(Object* other)
{
	Bullet* bullet = dynamic_cast<Bullet*>(other);
	if (bullet != nullptr) {
		ReceiveDamage(10);

		//enemyHealth -= 10;

		//std::cout << "ENEMY HEALTH: " << enemyHealth << std::endl;

		//if (enemyHealth <= 0)
		//{
		//	Destroy();
		//	std::cout << "MUELTO DIAVLO" << std::endl;
		//}
	}   
	//else if () { //HERE SHOULD GO THE PLAYER REFERENCE TO MAKE IT THAT IF THEY TOUCH, THE PLAYER LOSES HEALTH (SO IT PROBABLY NEEDS A MANAGER FOR THE ENTITIES TO MAKE IT EASIER)
	//					OR MAYBE PUTTING THIS INTERACTION IN THE PLAYER IS CORRECT TOO
	//}

}

void Enemy::Attack(IDamageable* other) const {
	std::cout << "Enemy attacks!" << std::endl;
}

void Enemy::ReceiveDamage(int damageToAdd) {
	enemyHealth -= damageToAdd;
	std::cout << "Enemy received " << damageToAdd << " damage. Health: " << enemyHealth << std::endl;

	if (enemyHealth <= 0) {
		// Destruir enemigo
		Destroy();
		std::cout << "Enemy Dead!" << std::endl;
	}
}

void Enemy::CircleMove() {
	Vector2 center = Vector2(RM->WINDOW_WIDTH / 1.3f, RM->WINDOW_HEIGHT / 2.f);

	float pi = 3.14159f;

	angle += angularSpeed * 0.02f;

	if (angle > 2 * pi)
		angle -= 2 * pi;

	Vector2 newPos(cos(angle) * radius, sin(angle) * radius);

	_transform->position = center + newPos;
}