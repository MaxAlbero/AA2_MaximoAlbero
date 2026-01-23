//#pragma once
//#include "Enemy.h"
//
//enum ReturnPhase {
//	DIAGONAL_MOVE,
//	HORIZONTAL_MOVE
//};
//
//enum BubbleDirection {
//	TOP_TO_BOTTOM,    // Aparece arriba, sale abajo
//	BOTTOM_TO_TOP     // Aparece abajo, sale arriba
//};
//
//class Bubbles : public Enemy {
//private:
//	float moveSpeed;
//	float stopPointX;
//
//	// Variables para movimiento circular
//	Vector2 circleCenter;
//	float circleRadius;
//	float circleAngle;
//	float circleSpeed; // velocidad angular en radianes por segundo
//	bool circleComplete;
//	int health;
//
//	ReturnPhase returnPhase;
//	float targetCenterY;
//
//	BubbleDirection direction;
//
//public:
//	Bubbles(BubbleDirection dir, float offsetX = 0.f)
//		: Enemy() {
//		_renderer = new ImageRenderer(_transform, "resources/pompa.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));
//
//		_transform->size = Vector2(100.f, 100.f);
//
//		direction = dir;
//
//		if (dir == TOP_TO_BOTTOM) {
//			_transform->position = Vector2(RM->WINDOW_WIDTH + offsetX, RM->WINDOW_HEIGHT / 5.f);
//		}
//		else {
//			_transform->position = Vector2(RM->WINDOW_WIDTH + offsetX, RM->WINDOW_HEIGHT * 4.f / 5.f);
//		}
//		_physics->AddCollider(new AABB(_transform->position, _transform->size));
//
//		moveSpeed = 100.f;
//		stopPointX = RM->WINDOW_WIDTH / 3.f;
//
//		currentState = SIMPLE_MOVE;
//
//		circleRadius = 100.f;      // Radio del círculo
//		circleAngle = 0.f;
//		circleSpeed = 3.0f;        // Radianes por segundo (ajusta la velocidad)
//		circleComplete = false;
//
//		returnPhase = DIAGONAL_MOVE;
//
//		health = 20;
//
//		if (dir == TOP_TO_BOTTOM)
//			targetCenterY = RM->WINDOW_HEIGHT / 1.5f;
//		else
//			targetCenterY = RM->WINDOW_HEIGHT / 3.f;
//	}
//
//	void Update() override {
//
//		switch (currentState) {
//		case SIMPLE_MOVE:
//			Move();
//			break;
//		case STAY:
//			EnemyBehaviour();
//			break;
//		case CIRCLE_MOVE:
//			CircleMove();
//			break;
//		case RETURN:
//			GoAway();
//			break;
//		}
//
//		// Destruir cuando sale de la pantalla
//		if (_transform->position.x > RM->WINDOW_WIDTH + _transform->size.x) {
//			std::cout << "Burbuja salió de la pantalla" << std::endl;
//			Destroy();
//		}
//
//		Object::Update();
//	}
//
//	//void OnCollision(Object* other) override;
//	void EnemyBehaviour() override {
//		// Aquí puedes añadir lógica antes de empezar el círculo
//		currentState = CIRCLE_MOVE;
//		circleCenter = _transform->position; // El centro del círculo es donde se detuvo
//		circleAngle = 0.f;
//		circleComplete = false;
//	}
//
//	void Move() override {
//		_physics->SetVelocity(Vector2(-moveSpeed, 0.f));
//
//		if (_transform->position.x <= stopPointX) {
//			currentState = STAY;
//			_physics->SetVelocity(Vector2(0.f, 0.f));
//
//		}
//	}
//
//	void CircleMove() override {
//		float pi = 3.14159f;
//
//		// Incrementar el ángulo según deltaTime
//		circleAngle += circleSpeed * TM.GetDeltaTime();
//
//		// Calcular nueva posición en el círculo
//		float newX = circleCenter.x + circleRadius * cos(circleAngle);
//		float newY = circleCenter.y + circleRadius * sin(circleAngle);
//
//		// Mover a la nueva posición
//		_transform->position = Vector2(newX, newY);
//
//		// Verificar si completó el círculo (360 grados = 2*PI radianes)
//		if (circleAngle >= 2.0f * pi) {
//			circleComplete = true;
//			circleAngle = 0.f;
//			currentState = RETURN;
//			_transform->position = circleCenter;
//		}
//	}
//
//	void GoAway() override {
//		switch (returnPhase) {
//		case DIAGONAL_MOVE: {
//			// Calcular dirección hacia la mitad de la pantalla
//			float directionX = 1.0f; // Siempre hacia la derecha
//
//			float directionY;
//			if (direction == TOP_TO_BOTTOM) {
//				// Comportamiento original: va hacia el centro y luego horizontal
//				directionY = (targetCenterY > _transform->position.y) ? 1.0f : -1.0f;
//			}
//			else {
//				// Nuevo comportamiento: va hacia el centro y luego horizontal
//				directionY = (targetCenterY > _transform->position.y) ? 1.0f : -1.0f;
//			}
//
//			// Normalizar para mantener velocidad constante
//			float magnitude = sqrt(directionX * directionX + directionY * directionY);
//			directionX /= magnitude;
//			directionY /= magnitude;
//
//			// Aplicar velocidad
//			_physics->SetVelocity(Vector2(directionX * moveSpeed, directionY * moveSpeed));
//
//			// Verificar si alcanzó la altura del centro (con tolerancia)
//			float tolerance = moveSpeed * TM.GetDeltaTime() * 2.0f;
//			if (abs(_transform->position.y - targetCenterY) <= tolerance) {
//				returnPhase = HORIZONTAL_MOVE;
//				_transform->position.y = targetCenterY; // Ajustar a la posición exacta
//				std::cout << "Alcanzó el centro, movimiento horizontal" << std::endl;
//			}
//			break;
//		}
//		case HORIZONTAL_MOVE:
//			// Moverse solo horizontalmente hacia la derecha
//			_physics->SetVelocity(Vector2(moveSpeed, 0.f));
//			break;
//		}
//	}
//};