#pragma once
#include "Enemy.h"
#include "LeftLinearMovement.h"
#include "RightLinearMovement.h"
#include "CirclePartialMovement.h"
#include "DiagonalMovement.h"

enum BubbleDirection { //TODO:REVIEW ALL THIS FILE AND CirclePartialMovement.h
	TOP_TO_BOTTOM,    // Aparece arriba, sale abajo (usa para centro vertical)
	BOTTOM_TO_TOP     // Aparece abajo, sale arriba
};

class Bubbles : public Enemy {
private:
	float moveSpeed;
	float stopPointX;

	// Parámetros de círculo
	float circleRadius;
	float circleAngularVelDeg; // grados por segundo
	float circleDegrees;       // grados a recorrer (300º)

	BubbleDirection direction;

public:
	Bubbles(BubbleDirection dir, float offsetX = 0.f)
		: Enemy(), direction(dir) {

		_renderer = new ImageRenderer(_transform, "resources/pompa.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));
		_transform->size = Vector2(100.f, 100.f);

		// Spawn a la derecha
		if (dir == TOP_TO_BOTTOM) {
			_transform->position = Vector2(RM->WINDOW_WIDTH + offsetX, RM->WINDOW_HEIGHT / 5.f);
		}
		else {
			_transform->position = Vector2(RM->WINDOW_WIDTH + offsetX, RM->WINDOW_HEIGHT * 4.f / 5.f);
		}

		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		// Parámetros
		moveSpeed = 300.f;
		stopPointX = RM->WINDOW_WIDTH / 3.f;

		circleRadius = 60.f;
		circleAngularVelDeg = 120.f; // grados por segundo (ajusta para la velocidad de giro)
		circleDegrees = 300.f;       // queremos 300º, no 360

		// Calcular centro Y del círculo según tipo de burbuja
		float centerY;
		if (dir == TOP_TO_BOTTOM)
			centerY = RM->WINDOW_HEIGHT / 3.f;
		else
			centerY = RM->WINDOW_HEIGHT / 1.5f;

		// Secuencia de movimientos:
		// 1) Mover hacia la izquierda hasta stopPointX
		movements.push_back(new LeftLinearMovement(_transform, _physics, stopPointX, moveSpeed));

		// 2) Hacer arco circular alrededor del centro en stopPointX,centerY
		Vector2 circleCenter = Vector2(stopPointX, centerY);
		movements.push_back(new CirclePartialMovement(_transform, _physics, circleRadius, circleCenter, circleAngularVelDeg, circleDegrees));

		float directionY;
		if (dir == TOP_TO_BOTTOM)
			directionY = RM->WINDOW_HEIGHT / 1.5f;
		else
			directionY = RM->WINDOW_HEIGHT / 3.f;
		movements.push_back(new DiagonalMovement(_transform, _physics, directionY, moveSpeed, 1.f));

		// 3) Salir en línea recta hacia la derecha (sin umbral)
		movements.push_back(new RightLinearMovement(_transform, _physics, moveSpeed));

		SetHealth(20);
		SetPointsValue(100);
	}

	void Update() override {
		// Comportamiento principal delega a Enemy::Update() que ejecuta movements
		Enemy::Update();

		// Destruir cuando sale de la pantalla por la derecha
		//if (_transform->position.x > RM->WINDOW_WIDTH + _transform->size.x) {
		//	Destroy();
		//}
	}
};