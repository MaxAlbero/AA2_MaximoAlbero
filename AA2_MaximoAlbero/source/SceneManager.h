#pragma once
#include "Scene.h"
#include <unordered_map>

#define SM SceneManager::Instance()

class SceneManager {
private:
	SceneManager() = default;
	SceneManager(SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	std::unordered_map<std::string, Scene*> _scenes;
	Scene* _currentScene = nullptr;
	std::string _nextScene = "";


public:
	static SceneManager& Instance() {
		static SceneManager instance;
		return instance;
	}

	bool AddScene(std::string name, Scene* scene) {
		if (_scenes.find(name) == _scenes.end()) {
			_scenes.emplace(name, scene);
			return true;
		}

		return false;
	}

	Scene* GetScene(std::string name) {
		if (_scenes.find(name) != _scenes.end()) {
			return _scenes[name];
		}

		return nullptr;
	}

	bool InitFirstScene(std::string name) {
		if (_scenes.find(name) != _scenes.end())
		{
			_currentScene = _scenes[name];
			_currentScene->OnEnter();
			return true;
		}

		return false;
	}

	Scene* GetCurrentScene() const { return _currentScene; }

	bool SetNextScene(std::string name) {
		if (_scenes.find(name) == _scenes.end()) {
			return false;
		}

		_nextScene = name;
		return true;
	}

	void UpdateCurrentScene() {
		if (_nextScene != "") {
			_currentScene->OnExit();
			_currentScene = _scenes[_nextScene];
			_currentScene->OnEnter();
			_nextScene = "";
		}

		_currentScene->Update();
	}


};