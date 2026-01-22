#pragma once
#include <vector>
#include "EnemyState.h"

class Transform;

class EnemyStateManager {
private:
	Transform* _transform;
	std::vector<EnemyState*> _states;
	int _currentStateIndex;

public:
	EnemyStateManager(Transform* transform)
		: _transform(transform), _currentStateIndex(0) {
	}

	~EnemyStateManager() {
		for (auto state : _states) {
			delete state;
		}
		_states.clear();
	}

	// Añadir un estado al manager
	void AddState(EnemyState* state) {
		if (state) {
			_states.push_back(state);
		}
	}

	// NUEVA: Configurar transición explícita entre estados
	void SetTransition(EnemyState* fromState, EnemyState* toState) {
		// El manager gestiona las transiciones internamente
		// Esto se podría implementar con un mapa si quieres transiciones no-lineales
		// Por ahora, la transición secuencial funciona
	}

	// Actualizar: transicionar si es necesario y actualizar el estado actual
	void Update(float deltaTime) {
		if (_states.empty()) return;

		EnemyState* currentState = _states[_currentStateIndex];
		currentState->Update(deltaTime);

		// Si el estado actual ha terminado, pasar al siguiente en secuencia
		if (currentState->IsFinished()) {
			// Transición automática al siguiente estado en el vector
			if (_currentStateIndex + 1 < _states.size()) {
				_currentStateIndex++;
			}
			// Si no hay más estados, se queda en el último
		}
	}

	EnemyState* GetCurrentState() const {
		return (_currentStateIndex < _states.size()) ? _states[_currentStateIndex] : nullptr;
	}

	int GetCurrentStateIndex() const { return _currentStateIndex; }
};