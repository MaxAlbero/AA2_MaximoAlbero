#pragma once
#include "Renderer.h"
#include "RenderManager.h"

class ImageRenderer : public Renderer
{
public:
	ImageRenderer(Transform* transform, std::string resourcePath, Vector2 sourceOffset, Vector2 sourceSize)
		: Renderer(transform, resourcePath) 
	{

		RM->GetTexture(resourcePath);

		_sourceRect = SDL_FRect{
			sourceOffset.x,
			sourceOffset.y,
			sourceSize.x,
			sourceSize.y
		};

		_destinationRect = SDL_FRect{
			transform->position.x,
			transform->position.y,
			transform->scale.x,
			transform->scale.y
		};
	}

	// Heredado vía Renderer
	virtual void Update(float dt) override{
		Vector2 offset = (Vector2(-_transform->size.x, -_transform->size.y) / 2.0f) * _transform->scale;

		_destinationRect.x = _transform->position.x + offset.x;
		_destinationRect.y = _transform->position.y + offset.y;

		_destinationRect.w = _transform->size.x * _transform->scale.x;
		_destinationRect.h = _transform->size.y * _transform->scale.y;
	}

	virtual void Render() override {
		SDL_RenderTextureRotated(
			RM->GetRenderer(),
			RM->GetTexture(_resourcePath),
			&_sourceRect,
			&_destinationRect,
			_transform->rotation,
			NULL,
			SDL_FLIP_NONE
		);
	}
};