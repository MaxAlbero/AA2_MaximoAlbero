#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cassert>
#include <string>
#include "Renderer.h"

#define FONT_PATH "resources/fonts/hyperspace.ttf"

class TextRenderer : public Renderer
{
protected:
	std::string _text;
	SDL_Texture* _textTexture;
	bool _autoSize = true;

public:
	TextRenderer(Transform* transform, std::string text)
		: Renderer(transform, FONT_PATH) {
		SetText(text);
	}
	~TextRenderer() {
		SDL_DestroyTexture(_textTexture);
		_textTexture = nullptr;
	}

	virtual void Update(float dt) override;
	virtual void Render() override;

	void SetText(std::string text);

	void SetColor(SDL_Color color) override {
		Renderer::SetColor(color);
		SetText(_text);
	}
};

