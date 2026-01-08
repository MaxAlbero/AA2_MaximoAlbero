#include "TextRenderer.h"
#include "RenderManager.h"

void TextRenderer::Update(float dt)
{
	Vector2 offset = (Vector2(-_transform->size.x, -_transform->size.y) / 2.0f) * _transform->scale;

	_destinationRect.x = _transform->position.x + offset.x;
	_destinationRect.y = _transform->position.y + offset.y;

	if (_autoSize) {
		_destinationRect.w = _sourceRect.w * _transform->scale.x;
		_destinationRect.h = _sourceRect.h * _transform->scale.y;
	}
	else {
		_destinationRect.w = _transform->size.x * _transform->scale.x;
		_destinationRect.h = _transform->size.y * _transform->scale.y;
	}
}

void TextRenderer::Render()
{
	SDL_RenderTextureRotated(
		RM->GetRenderer(),
		_textTexture,
		&_sourceRect,
		&_destinationRect,
		_transform->rotation,
		NULL,
		SDL_FLIP_NONE
	);
}

void TextRenderer::SetText(std::string text)
{
	//1)Destruir la textura (que té el text anterior)
	if (_textTexture != nullptr) {
		SDL_DestroyTexture(_textTexture);
	}

	//2)Crear surface
	SDL_Surface* surf = TTF_RenderText_Solid(
		RM->GetFont(_resourcePath),
		text.c_str(),
		text.length(),
		_color
	);
	assert(surf);

	//3)Crear textura
	_textTexture = SDL_CreateTextureFromSurface(RM->GetRenderer(), surf);
	SDL_DestroySurface(surf);
	assert(_textTexture);

	//4)Definir source rect
	_sourceRect = { 0.0f, 0.0f, (float)surf->w, (float)surf->h };

	//5)Actualitzar string
	_text = text;
}