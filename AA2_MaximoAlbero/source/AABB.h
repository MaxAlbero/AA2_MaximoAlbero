#pragma once
#include "Vector2.h"

class AABB {
protected:
	Vector2 _topLeft;
	Vector2 _size;
public:
	AABB(Vector2 topLeft, Vector2 size)
		: _topLeft(topLeft), _size(size) {}

	Vector2 const GetTopLeft() { return _topLeft; }
	Vector2 const GetSize() { return _size; }
	void SetTopLeft(Vector2 newTopLeft) { _topLeft = newTopLeft; }
	void SetSize(Vector2 newSize) { _size = newSize; }

	bool CheckOverlappingPoint(Vector2 point);
	bool CheckOverlappingAABB(const AABB* other); //const abans del parametre per evitar modificacions i errors
};