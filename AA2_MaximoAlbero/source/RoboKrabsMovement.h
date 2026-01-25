#pragma once //TODO: REVIEW ALL THIS CODE TO MAKE IT LIKE THE ORIGINAL GAME
#include "EnemyMovement.h"
#include <random>
#include <cmath>

// Movimiento específico para RoboKrabs:
// - se queda "pegado" a una pared (posición de attach)
// - espera un intervalo aleatorio [minDelay, maxDelay]
// - salta hacia la posición actual del player (velocidad jumpSpeed)
// - al llegar, vuelve a la posición de attach (velocidad returnSpeed)
// - repite el ciclo indefinidamente
class RoboKrabsMovement : public EnemyMovement {
private:
	Transform* _playerTransform;
	Vector2 _attachPos;
	bool _attachToCeiling;
	float _jumpSpeed;
	float _returnSpeed;
	float _minDelay;
	float _maxDelay;
	float _timer;
	float _currentDelay;
	float _tolerance;

	enum Phase { WAITING, JUMPING, RETURNING } _phase;

	// RNG para retraso aleatorio
	std::mt19937 _rng;
	std::uniform_real_distribution<float> _dist;

	// target dinámico para salto/retorno
	Vector2 _currentTarget;

	static float DistanceSq(const Vector2& a, const Vector2& b) {
		float dx = a.x - b.x; float dy = a.y - b.y; return dx * dx + dy * dy;
	}

public:
	// playerTransform: referencia al transform del jugador
	// attachPos: posición en pared donde se "pega" inicialmente
	// attachToCeiling: no usado directamente pero semántico (puedes usarlo para orientación)
	RoboKrabsMovement(Transform* transform, RigidBody* rigidBody,
		Transform* playerTransform,
		const Vector2& attachPos,
		bool attachToCeiling,
		float jumpSpeed = 600.f,
		float returnSpeed = 400.f,
		float minDelay = 3.f,
		float maxDelay = 5.f,
		float tolerance = 12.f)
		: EnemyMovement(transform, rigidBody),
		_playerTransform(playerTransform),
		_attachPos(attachPos),
		_attachToCeiling(attachToCeiling),
		_jumpSpeed(jumpSpeed),
		_returnSpeed(returnSpeed),
		_minDelay(minDelay),
		_maxDelay(maxDelay),
		_timer(0.f),
		_phase(WAITING),
		_rng(std::random_device{}()),
		_dist(minDelay, maxDelay),
		_currentTarget(attachPos),
		_tolerance(tolerance)
	{
		_currentDelay = _dist(_rng);
		// asegurar que start en attachPos
		if (_transform) _transform->position = _attachPos;
	}

	void Update(float deltaTime) override {
		if (!_transform) return;

		// si no hay player, permanecer pegado
		if (!_playerTransform) {
			_phase = WAITING;
			if (_rigidBody) _rigidBody->SetVelocity(Vector2(0.f, 0.f));
			return;
		}

		switch (_phase) {
		case WAITING: {
			_timer += deltaTime;
			// permanecer pegado
			if (_rigidBody) _rigidBody->SetVelocity(Vector2(0.f, 0.f));
			// iniciar salto cuando termine el delay
			if (_timer >= _currentDelay) {
				_timer = 0.f;
				_currentDelay = _dist(_rng);
				_phase = JUMPING;
				// fijar target en la posición actual del jugador
				_currentTarget = _playerTransform->position;
				// calcular dirección y aplicar velocidad
				Vector2 dir = _currentTarget - _transform->position;
				float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
				if (dist > 0.001f) {
					dir.x /= dist; dir.y /= dist;
					if (_rigidBody) _rigidBody->SetVelocity(dir * _jumpSpeed);
					else _transform->position = _transform->position + dir * (_jumpSpeed * deltaTime);
				}
			}
			break;
		}
		case JUMPING: {
			// comprobar llegada al target (player pos en el momento del salto)
			float d2 = DistanceSq(_transform->position, _currentTarget);
			if (d2 <= _tolerance * _tolerance) {
				// detener
				if (_rigidBody) _rigidBody->SetVelocity(Vector2(0.f, 0.f));
				// preparar retorno al attach
				_phase = RETURNING;
				_currentTarget = _attachPos;
				// aplicar velocidad de retorno
				Vector2 dir = _currentTarget - _transform->position;
				float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
				if (dist > 0.001f) {
					dir.x /= dist; dir.y /= dist;
					if (_rigidBody) _rigidBody->SetVelocity(dir * _returnSpeed);
					else _transform->position = _transform->position + dir * (_returnSpeed * deltaTime);
				}
			}
			else {
				// actualizar la velocidad en caso de que el salto deba ajustarse frame a frame
				Vector2 dir = _currentTarget - _transform->position;
				float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
				if (dist > 0.001f) {
					dir.x /= dist; dir.y /= dist;
					if (_rigidBody) _rigidBody->SetVelocity(dir * _jumpSpeed);
				}
			}
			break;
		}
		case RETURNING: {
			float d2 = DistanceSq(_transform->position, _currentTarget);
			if (d2 <= _tolerance * _tolerance) {
				// volver al attach exacto y esperar de nuevo
				_transform->position = _attachPos;
				if (_rigidBody) _rigidBody->SetVelocity(Vector2(0.f, 0.f));
				_phase = WAITING;
				_timer = 0.f;
				_currentDelay = _dist(_rng);
			}
			else {
				// asegurar velocidad de retorno
				Vector2 dir = _currentTarget - _transform->position;
				float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
				if (dist > 0.001f) {
					dir.x /= dist; dir.y /= dist;
					if (_rigidBody) _rigidBody->SetVelocity(dir * _returnSpeed);
				}
			}
			break;
		}
		}
	}
};