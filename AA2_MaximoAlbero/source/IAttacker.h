#pragma once
#include "IDamageable.h"

class IAttacker {
public:
	virtual ~IAttacker() = default;
	virtual void Attack(IDamageable* other) const = 0; // case of player: other -> enemy / case of enemy: other -> player 
};