#pragma once
#include "Object.h"
#include "AnimatedImageRenderer.h"

class AnimatedImageObject : public Object
{
public:
	AnimatedImageObject(std::string texturePath, Vector2 sourceOffset, Vector2 sourceSize,
		int numFrames, int numColumns, float frameWidth, float frameHeight, bool looping
		) : Object() {
		_renderer = new AnimatedImageRenderer(_transform, texturePath, sourceOffset, sourceSize,
			numFrames, numColumns, frameWidth, frameHeight, looping);
	}
};