#pragma once
#include "Spawner.h"
#include "Object.h"
#include <vector>

class Scene {
protected:
	std::vector<Object*> _objects;
	std::vector<Object*> _ui;

public:
	Scene() = default;
	virtual void OnEnter() = 0;
	virtual void OnExit() {  //Neteja la memoria (al ser un virtual, els fills poden fer-li override i si volen no eliminar certs objectes que necessitem)
		
		SPAWNER.ClearSpawner();

		//Destruir TOTS els objectes (de joc i UI)
		for (Object* o : _objects) {
			delete o;
		}

		_objects.clear();

		for (Object* u : _ui) {
			delete u;
		}

		_ui.clear();
	}

	virtual void Update() 
	{
		//1) Destruir
		for (int i = _objects.size() - 1; i >= 0; i--)
		{
			if (_objects[i]->IsPendingDestroy())
			{
				delete _objects[i];
				_objects.erase(_objects.begin() + i);
			}
		}

		for (int i = _ui.size() - 1; i >= 0; i--) {
			if (_ui[i]->IsPendingDestroy()) {
				delete _ui[i];
				_ui.erase(_ui.begin() + i);
			}
		}

		//2) SPAWNING
		while (SPAWNER.AreObjectsPendingSpawn()) {
			_objects.push_back(SPAWNER.GetSpawnedObject());
		}

		//2) Actualizar
		for (Object* o : _objects) {
			o->Update();
		}

		for (Object* u : _ui) {
			u->Update();
		}

		//3) Comprovar col·lisions
		int size = _objects.size();
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < _objects.size(); j++) {
				if (_objects[i]->GetRigidBody()->CheckCollision(_objects[j]->GetRigidBody())) {
					_objects[i]->OnCollision(_objects[j]);
					_objects[j]->OnCollision(_objects[i]);
				}
			}
		}

		size = _ui.size();
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < _ui.size(); j++)
			{
				if (_ui[i]->GetRigidBody()->CheckCollision(_ui[j]->GetRigidBody()))
				{
					//...
				}
			}
		}
	}

	virtual void Render() {
		for (Object* o : _objects) {
			o->Render();
		}

		for (Object* u : _ui) {
			u->Render();
		}
	}
};