#pragma once
#include "Vector2.h"

class Transform;

class EnemyState {
public:
	virtual ~EnemyState() {}

	// Actualizar el estado cada frame
	virtual void Update(float deltaTime) = 0;

	// Indica si el estado ha terminado y debe transicionar
	virtual bool IsFinished() const = 0;

	// Retorna el siguiente estado (nullptr si continúa en éste)
	virtual EnemyState* NextState() = 0;
};