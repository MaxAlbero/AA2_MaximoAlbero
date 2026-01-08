#pragma once
#include "SDL3/SDL.h"
#include <unordered_map>

#define IM InputManager::GetInstance()

enum KeyState { EMPTY, DOWN, UP, HOLD, RELEASED };

class InputManager
{
public:
	static InputManager* GetInstance() {
		static InputManager instance;
		return &instance;
	}

	bool Listen();

	float GetMouseX() const { return _mouseX; }
	float GetMouseY() const { return _mouseY; }
	bool GetLeftClick() const { return _leftClick; }
	bool GetEvent(Sint32 input, KeyState inputValue);

private:
	InputManager() = default;
	InputManager(InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	~InputManager() {}

	//Posició del ratolí
	float _mouseX, _mouseY;
	bool _leftClick;

	std::unordered_map<Sint32, KeyState> _keyReference;
};

