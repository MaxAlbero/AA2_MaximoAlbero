#pragma once
#include <SDL3/SDL.h>
#include <string>
#include "Vector2.h"
#include "Transform.h"
#include "Renderer.h"
#include "RigidBody.h"


class Object{
private:
	bool _isPendingDestroy = false;

protected:
	Renderer* _renderer = nullptr;
	Transform* _transform;
	RigidBody* _physics;

public:
	Object() {
		_transform = new Transform();
		_physics = new RigidBody(_transform);
	}
	~Object() {
		delete _transform;
		_transform = nullptr;

		delete _renderer;
		_renderer = nullptr;

		delete _physics;
		_physics = nullptr;
	}
	virtual void Update() { 
		if (_physics != nullptr)
			_physics->Update(0.02f);

		_renderer->Update(0.02f); //50 FPS
	} 
	virtual void Render() {	_renderer->Render(); }
	Transform* GetTransform() { return _transform; }
	RigidBody* GetRigidBody() { return _physics; }
	virtual void OnCollision(Object* other) {}
	//De moment no fan res
	bool IsPendingDestroy() const { return _isPendingDestroy; }
	virtual void Destroy() { _isPendingDestroy = true; }
};