#pragma once
#include <queue>
#include "Object.h"

#define SPAWNER Spawner::Instance()

class Spawner { //Spawner es un Singleton
public:
	static Spawner& Instance() {
		static Spawner spawner;
		return spawner;
	}

	void SpawnObject(Object* obj) { spawnedObjects.push(obj); } //añade objetos a la queue
	bool AreObjectsPendingSpawn() { return !spawnedObjects.empty(); } //comprobar si aun quedan elementos en la queue
	Object* GetSpawnedObject() {
		if (!AreObjectsPendingSpawn()) {
			return nullptr;
		}

		Object* temp = spawnedObjects.front();
		spawnedObjects.pop();
		return temp;
	}
	void ClearSpawner() {
		while (AreObjectsPendingSpawn()) //esta funcion solo dice "not empty" mientras aun hayan elementos en la queue
		{
			delete spawnedObjects.front(); 
			spawnedObjects.pop();
		}
	}

	int GetSpawnedObjectCount() {
		return spawnedObjects.size();
	}

private:
	Spawner() = default;
	Spawner(Spawner&) = delete;
	Spawner& operator=(const Spawner&) = delete;

	std::queue<Object*> spawnedObjects;
};