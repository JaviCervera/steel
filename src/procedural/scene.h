#pragma once

#include "common.h"

struct Camera;

extern "C"
{
	EXPORT void CALL DrawScene(const Camera *camera);
	EXPORT void CALL GetScreenCoords(const Camera *camera, float x, float y, float z);
	EXPORT void CALL GetSceneCoords(const Camera *camera, float x, float y, float depth);
	EXPORT float CALL GetCoordX();
	EXPORT float CALL GetCoordY();
	EXPORT float CALL GetCoordZ();
}
