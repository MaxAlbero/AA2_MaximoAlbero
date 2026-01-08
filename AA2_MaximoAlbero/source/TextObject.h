#pragma once
#include "Object.h"
#include "TextRenderer.h"

class TextObject : public Object {
public:
	TextObject(std::string text)
		: Object() {
		_renderer = new TextRenderer(_transform, text);
		_renderer->SetColor({ 0xFF,0xFF,0xFF,0xFF });
	}

	void SetText(std::string text) {
		dynamic_cast<TextRenderer*>(_renderer)->SetText(text); //como sabemos que el renderer sera un TextRenderer 
														//podemos permitirnos usar dynamic_cast, pero no es bueno/seguro hacer esto
	}
};