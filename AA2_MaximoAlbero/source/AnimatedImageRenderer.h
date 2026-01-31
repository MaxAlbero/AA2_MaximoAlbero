#pragma once
#include "ImageRenderer.h"
#include "TimeManager.h"

class AnimatedImageRenderer : public ImageRenderer {
private:
	int _numFrames;
	int _numColumns;
	int _currentFrame;
	float _frameWidth;
	float _frameHeight;

	bool _looping;
	float _currentFrameTime;

public:
	AnimatedImageRenderer(Transform* transform, std::string resourcePath, Vector2 sourceOffset, Vector2 sourceSize,
		int numFrames, int numColumns, float frameWidth, float frameHeight, bool looping) 
		: ImageRenderer(transform, resourcePath, sourceOffset, sourceSize),
		_numFrames(numFrames), _numColumns(numColumns), _frameWidth(frameWidth), _frameHeight(frameHeight), _looping(looping), 
		_currentFrameTime(0.0f), _currentFrame(0)
	{
		_sourceRect = SDL_FRect{
			sourceOffset.x,
			sourceOffset.y,
			frameWidth,
			frameHeight
		};
	}

	virtual void Update(float dt) override {
		//1) Actualizar el destRect
		ImageRenderer::Update(dt);

		//2) Actualizar el tiempo que ha pasado desde el inicio del frame
		_currentFrameTime += dt;

		//3) Comprobar si la duración de este frame es mayor que la duración máxima
		if (_currentFrameTime >= TM.GetFrameTime())
		{
			//4) Incrementar el número del frame
			_currentFrame++;
			//5) Resetear la duración del nuevo frame
			_currentFrameTime = 0.f;
			//6) Comprobar si el anterior era el último frame
			if (_currentFrame >= _numFrames) {


				//7.a) Si se reproduce un bucle -> Reiniciar el ciclo de la animación
				if (_looping)
					_currentFrame = 0;
				//7.b) SI no se reproduce un bucle -> Congelar y quedarse en el último frame
				else
					_currentFrame = _numFrames - 1;
			}
			//8) Calcular la celda en la spritesheet del frame actual
			int currentRow = _currentFrame / _numColumns;
			int currentColumn = _currentFrame % _numColumns;

			//9) Poner en el sourceRect los píxeles de la celda
			_sourceRect.x = currentColumn * _frameWidth;
			_sourceRect.y = currentRow * _frameHeight;
		}
	}

	virtual void Render() {
		ImageRenderer::Render();
	}
};