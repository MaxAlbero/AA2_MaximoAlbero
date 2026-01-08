#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

#include "Transform.h"


class Renderer
{
protected:
	Transform* _transform;
	SDL_Color _color;
	SDL_FRect _sourceRect;
	SDL_FRect _destinationRect;
	std::string _resourcePath;

public:
	Renderer(Transform* transform, std::string resourcePath)
		: _transform(transform), _resourcePath(resourcePath){}
	~Renderer() {}
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual void SetDestinationRect(SDL_FRect rect) {
		_destinationRect = rect;
	}

	virtual void SetColor(SDL_Color color) { _color = color; }
	SDL_Color GetColor() { return _color; }
};