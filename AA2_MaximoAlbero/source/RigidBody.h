#pragma once
#include "AABB.h"
#include "Transform.h"
#include <vector>

class RigidBody {
private:
	std::vector<AABB*> _colliders;
	Transform* _transform;

	Vector2 _velocity;
	float _angularVelocity;

	Vector2 _acceleration;
	float _angularAcceleration;

	float _linearDrag;
	float _angularDrag;

public:
	RigidBody(Transform* transform)
		: _transform(transform), _velocity(Vector2()), _angularVelocity(0.0f),
		_acceleration(Vector2()), _angularAcceleration(0.0f),
		_linearDrag(0.0f), _angularDrag(0.0f) {}

	~RigidBody() {
		for (AABB* collider : _colliders)
		{
			delete collider;
		}

		_colliders.clear();
	}

	void AddCollider(AABB* collider) { _colliders.push_back(collider); }

	void AddForce(Vector2 force) { _acceleration = _acceleration + force; } //asumim que tots els RigidBody pesen 1 unitat
	void AddTorque(float amount) { _angularAcceleration += amount; }
	Vector2 const GetVelocity() { return _velocity; }
	void SetVelocity(Vector2 velocity) { _velocity = velocity; }
	void SetLinearDrag(float linearDrag) { _linearDrag = linearDrag; }
	void SetAngularDrag(float angularDrag) { _angularDrag = angularDrag; }

	bool CheckCollision(const RigidBody* other);
	bool ChecckOverlappingPoint(Vector2 point);

	void Update(float dt);
};